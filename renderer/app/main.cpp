//
// main.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:50.
//

#include "VSoftRenderer/DirectionalLight.h"
#include "VSoftRenderer/FrameBuffer.h"
#include "VSoftRenderer/Matrix4.h"
#include "VSoftRenderer/Texture2D.h"
#include "VSoftRenderer/Triangle3D.h"
#include "VSoftRenderer/Utils.h"
#include "VSoftRenderer/VGL.h"

#include <raylib-cpp.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <iostream>

const int ScreenWidth = 800;
const int ScreenHeight = 800;

void DrawFrameBuffer()
{
    auto frameBufferSize = VSoftRenderer::FrameBuffer::GetInstance()->GetSize();
    for (int i = 0; i < frameBufferSize.X; ++i)
    {
        for (int j = 0; j < frameBufferSize.Y; ++j)
        {
            auto color = VSoftRenderer::FrameBuffer::GetInstance()->GetPixel(i, j).PixelColor;
            DrawPixel(i, j, {color.R, color.G, color.B, color.A});
        }
    }
}

int main() 
{
    raylib::Window window(ScreenWidth, ScreenHeight, "VSoftRenderer");
    raylib::RenderTexture2D renderTexture(ScreenWidth, ScreenHeight);
    raylib::Texture targetTexture(renderTexture.GetTexture());

    SetTargetFPS(60);

    // Load a model from disk by using tinyobjloader
    std::string inputFile = "resources/models/obj/african_head.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputFile.c_str());

    if (!warn.empty())
    {
        std::cout << warn << std::endl;
    }

    if (!err.empty())
    {
        std::cerr << err << std::endl;
    }

    if (!ret)
    {
        return -1;
    }

    // Load a texture image from disk
    auto textureImageData = raylib::Image("resources/textures/tga/african_head_diffuse.tga");
    if (!textureImageData.IsReady())
    {
        std::cerr << "Failed to load texture!!!" << std::endl;
        return -2;
    }

    int textureImageWidth  = textureImageData.width;
    int textureImageHeight = textureImageData.height;
    VSoftRenderer::Color* textureColors = (VSoftRenderer::Color*)LoadImageColors(textureImageData);
    VSoftRenderer::Texture2D texture(textureImageWidth, textureImageHeight, textureColors);

    VSoftRenderer::DirectionalLight light({0, 0, -1});

    VSoftRenderer::glViewPort(0, 0, ScreenWidth, ScreenHeight);

    VSoftRenderer::glClearColor({50, 50, 50, 255});
    VSoftRenderer::glClear();

    // Camera parameters
    VSoftRenderer::Vector3Float eye(1 , 1, 3);
    VSoftRenderer::Vector3Float center(0 , 0, 0);
    VSoftRenderer::Vector3Float up(0 , 1, 0);

    VSoftRenderer::Matrix4 modelMatrix = VSoftRenderer::Matrix4::Identity();
    VSoftRenderer::Matrix4 viewMatrix = VSoftRenderer::glLookAt(eye, center, up);
    VSoftRenderer::Matrix4 projectionMatrix = VSoftRenderer::glProjection(eye, center);

    VSoftRenderer::Matrix4 modelViewProjectionViewportMatrix = VSoftRenderer::g_vglState.ViewportMatrix * projectionMatrix * viewMatrix * modelMatrix;

    // Flat Shading Renderer
    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++)
    {
        // Loop over faces(polygon)
        size_t indexOffset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            auto fv = static_cast<size_t>(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            VSoftRenderer::Vector3Int   screenCoords[3];
            VSoftRenderer::Vector3Float worldCoords[3];
            VSoftRenderer::Vector2Float uvCoords[3];
            for (size_t vId = 0; vId < 3; vId++)
            {
                auto index = shapes[s].mesh.indices[indexOffset + vId];

                float x = attrib.vertices[3*static_cast<size_t>(index.vertex_index)+0];
                float y = attrib.vertices[3*static_cast<size_t>(index.vertex_index)+1];
                float z = attrib.vertices[3*static_cast<size_t>(index.vertex_index)+2];

                worldCoords[vId] = { x, y, z };
                screenCoords[vId] = VSoftRenderer::Utils::Vector3Float2Int(modelViewProjectionViewportMatrix * worldCoords[vId]);

                float u = attrib.texcoords[2*static_cast<size_t>(index.texcoord_index)+0];
                float v = attrib.texcoords[2*static_cast<size_t>(index.texcoord_index)+1];
                uvCoords[vId] = {u, v};
            }

            VSoftRenderer::Vector3Float normal = (worldCoords[2] - worldCoords[0]).CrossProduct(worldCoords[1] - worldCoords[0]).Normalized();
            float intensity = normal * light.GetDirection();
            intensity = std::max(0.0f, intensity);
            VSoftRenderer::Triangle3D::DrawInterpolated(screenCoords[0],
                                                        screenCoords[1],
                                                        screenCoords[2],
                                                        uvCoords,
                                                        texture,
                                                        intensity);
            indexOffset += fv;
        }

    }

    while (!window.ShouldClose())
    {
        renderTexture.BeginMode();
            // Draw FrameBuffer
            DrawFrameBuffer();
        renderTexture.EndMode();

        BeginDrawing();
            window.ClearBackground(BLACK);
            targetTexture.Draw(0, 0);
        EndDrawing();
    }

    return 0;
}