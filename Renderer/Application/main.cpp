//
// main.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:50.
//

#include "VGL/DirectionalLight.h"
#include "VGL/FrameBuffer.h"
#include "VGL/Matrix4.h"
#include "VGL/VGL.h"

#include <raylib-cpp.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <iostream>

using namespace VGL;

const int ScreenWidth = 800;
const int ScreenHeight = 800;

void DrawFrameBuffer()
{
    auto frameBufferSize = FrameBuffer::GetInstance()->GetSize();
    for (int i = 0; i < frameBufferSize.X; ++i)
    {
        for (int j = 0; j < frameBufferSize.Y; ++j)
        {
            auto color = FrameBuffer::GetInstance()->GetPixel(i, j).PixelColor;
            DrawPixel(i, j, {color.R, color.G, color.B, color.A});
        }
    }
}

struct GouraudShader : public VGLShaderBase
{
    int BindDiffuseTextureSlot;
    int BindNormalTextureSlot;

    Vector3Float UniformLightDirection;
    Matrix4      UniformMVP;
    Matrix4      UniformMVPIT;

    std::vector<Vector2Float> VaryingUVs {3};

    virtual void vert(int faceIndex, int vertexIndexInFace, Vector3Float& gl_Position) override
    {
        VaryingUVs[vertexIndexInFace] = TargetMesh->GetUV(faceIndex, vertexIndexInFace);
        gl_Position = UniformMVP * gl_Position;
    }

    virtual bool frag(Vector3Float bc, VGL::Color& gl_FragColor) override
    {
        Vector2Float uv = VaryingUVs[0] * bc.X + VaryingUVs[1] * bc.Y + VaryingUVs[2] * bc.Z;
        Vector3Float n = (UniformMVPIT * sample2D(BindNormalTextureSlot, uv.X, uv.Y).XYZ()).Normalized();
        Vector3Float l = (UniformMVP * UniformLightDirection).Normalized();
        float intensity = std::max(0.0f, n * l);
        gl_FragColor = sample2D(BindDiffuseTextureSlot, uv.X, uv.Y) * intensity;
        return false;
    }
};

int main() 
{
    raylib::Window window(ScreenWidth, ScreenHeight, "VSoftRenderer");
    raylib::RenderTexture2D renderTexture(ScreenWidth, ScreenHeight);
    raylib::Texture targetTexture(renderTexture.GetTexture());

    // Load a model from disk
    std::string modelFile = "Resources/Models/african_head/african_head.obj";
    tinyobj::ObjReaderConfig readerConfig;
    readerConfig.mtl_search_path = "./"; // Path to material files

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(modelFile, readerConfig))
    {
        if (!reader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        return -1;
    }

    if (!reader.Warning().empty())
    {
        std::cout << "TinyObjReader: " << reader.Warning();
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    std::vector<VGL::Mesh> meshes;

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++)
    {
        VGL::Mesh mesh = {};
        mesh.Vertices.resize(attrib.vertices.size());
        mesh.Normals.resize(attrib.normals.size());
        mesh.TextureCoords.resize(attrib.texcoords.size());

        // Loop over faces(polygon)
        size_t indexOffset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            TriangleFace face = {};

            size_t fv = static_cast<size_t>(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            int vertexIndex = 0;
            for (size_t v = 0; v < fv; v++)
            {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[indexOffset + v];
                vertexIndex = static_cast<size_t>(idx.vertex_index);

                tinyobj::real_t vx = attrib.vertices[3*static_cast<size_t>(idx.vertex_index)+0];
                tinyobj::real_t vy = attrib.vertices[3*static_cast<size_t>(idx.vertex_index)+1];
                tinyobj::real_t vz = attrib.vertices[3*static_cast<size_t>(idx.vertex_index)+2];

                mesh.Vertices[vertexIndex] = { vx, vy, vz };
                face.VertexIndices.push_back(vertexIndex);

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0)
                {
                    tinyobj::real_t nx = attrib.normals[3*static_cast<size_t>(idx.normal_index)+0];
                    tinyobj::real_t ny = attrib.normals[3*static_cast<size_t>(idx.normal_index)+1];
                    tinyobj::real_t nz = attrib.normals[3*static_cast<size_t>(idx.normal_index)+2];

                    auto normalIndex = static_cast<size_t>(idx.normal_index);

                    mesh.Normals[normalIndex] = { nx, ny, nz };
                    face.NormalIndices.push_back(normalIndex);
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0)
                {
                    tinyobj::real_t tx = attrib.texcoords[2*static_cast<size_t>(idx.texcoord_index)+0];
                    tinyobj::real_t ty = attrib.texcoords[2*static_cast<size_t>(idx.texcoord_index)+1];

                    auto texCoordIndex = static_cast<size_t>(idx.texcoord_index);

                    mesh.TextureCoords[texCoordIndex] = { tx, ty };
                    face.TextureCoordIndices.push_back(texCoordIndex);
                }

                // Optional: vertex colors
                // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
                // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
                // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
            }
            indexOffset += fv;
            mesh.Faces.push_back(face);

            // per-face material
            shapes[s].mesh.material_ids[f];
        }

        meshes.push_back(mesh);
    }

    SetTargetFPS(60);

    // Load a diffuse texture image from disk
    auto diffuseTextureImageData = raylib::Image("Resources/Textures/african_head/african_head_diffuse.tga");
    if (!diffuseTextureImageData.IsReady())
    {
        std::cerr << "Failed to load texture!!!" << std::endl;
        return -2;
    }

    int diffuseTextureImageWidth  = diffuseTextureImageData.width;
    int diffuseTextureImageHeight = diffuseTextureImageData.height;
    VGL::Color* diffuseTextureColors = (VGL::Color*)LoadImageColors(diffuseTextureImageData);
    VGL::Texture2D diffuseTexture(diffuseTextureImageWidth, diffuseTextureImageHeight, diffuseTextureColors);

    auto normalTextureImageData = raylib::Image("Resources/Textures/african_head/african_head_nm.tga");
    if (!normalTextureImageData.IsReady())
    {
        std::cerr << "Failed to load texture!!!" << std::endl;
        return -2;
    }

    int normalTextureImageWidth  = normalTextureImageData.width;
    int normalTextureImageHeight = normalTextureImageData.height;
    VGL::Color* normalTextureColors = (VGL::Color*)LoadImageColors(normalTextureImageData);
    VGL::Texture2D normalTexture(normalTextureImageWidth, normalTextureImageHeight, normalTextureColors);

    DirectionalLight light(Vector3Float(1, 1, 1).Normalized());

    glViewPort(0, 0, ScreenWidth, ScreenHeight);

    glClearColor({50, 50, 50, 255});
    glClear();

    // Camera parameters
    Vector3Float eye(1 , 1, 3);
    Vector3Float center(0 , 0, 0);
    Vector3Float up(0, 1, 0);

    Matrix4 modelMatrix = Matrix4::Identity();
    Matrix4 viewMatrix = glLookAt(eye, center, up);
    Matrix4 projectionMatrix = glProjection(eye, center);

    Matrix4 mvp = projectionMatrix * viewMatrix * modelMatrix;

    glBindTexture(0, diffuseTexture);
    glBindTexture(1, normalTexture);

    GouraudShader shader = {};
    shader.UniformMVP = mvp;
    shader.UniformMVPIT = mvp.InverseTranspose();
    shader.UniformLightDirection = light.GetDirection();
    shader.BindDiffuseTextureSlot = 0;
    shader.BindNormalTextureSlot = 1;

    glBindShader(0, &shader);

    for (int meshIndex = 0; meshIndex < meshes.size(); ++meshIndex)
    {
        glBindMesh(meshIndex, meshes[meshIndex]);
        glUseShaderProgram(0);
        glDrawMeshIndexed(meshIndex);
    }

    while (!window.ShouldClose())
    {
        renderTexture.BeginMode();
            // Draw FrameBuffer
            DrawFrameBuffer();
        renderTexture.EndMode();

        BeginDrawing();
            window.ClearBackground(raylib::Color::Black());
            targetTexture.Draw(0, 0);
        EndDrawing();
    }

    return 0;
}