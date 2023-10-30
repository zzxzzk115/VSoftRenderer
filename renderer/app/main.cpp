//
// main.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:50.
//

#include "VSoftRenderer/FrameBuffer.h"
#include "VSoftRenderer/Line.h"
#include "VSoftRenderer/RenderConfig.h"
#include "VSoftRenderer/Triangle3D.h"
#include "VSoftRenderer/Utils.h"

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

    VSoftRenderer::RenderConfig::SetFrameBufferSize({ScreenWidth, ScreenHeight});

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
        exit(1);
    }

    VSoftRenderer::Vector3Float lightDirection(0, 0, -1);

    while (!window.ShouldClose())
    {
        renderTexture.BeginMode();

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
                    VSoftRenderer::Vector3Int* screenCoords = new VSoftRenderer::Vector3Int[fv];
                    VSoftRenderer::Vector3Float * worldCoords = new VSoftRenderer::Vector3Float[fv];
                    for (size_t v = 0; v < fv; v++)
                    {
                        auto index = shapes[s].mesh.indices[indexOffset + v];

                        float x = attrib.vertices[3*static_cast<size_t>(index.vertex_index)+0];
                        float y = attrib.vertices[3*static_cast<size_t>(index.vertex_index)+1];
                        float z = attrib.vertices[3*static_cast<size_t>(index.vertex_index)+2];

                        worldCoords[v] = { x, y, z};
                        screenCoords[v] = VSoftRenderer::Utils::World2Screen(worldCoords[v]);
                    }

                    VSoftRenderer::Vector3Float normal = (worldCoords[2] - worldCoords[0]).CrossProduct(worldCoords[1] - worldCoords[0]).Normalized();
                    float intensity = normal * lightDirection;
                    if (intensity > 0)
                    {
                        VSoftRenderer::Triangle3D::DrawFilled(screenCoords[0],
                                                            screenCoords[1],
                                                            screenCoords[2],
                                                            {
                                                                static_cast<unsigned char>(intensity * 255.0f),
                                                                static_cast<unsigned char>(intensity * 255.0f),
                                                                static_cast<unsigned char>(intensity * 255.0f),
                                                                255});
                    }

                    delete[] screenCoords;
                    delete[] worldCoords;
                    indexOffset += fv;
                }

            }

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