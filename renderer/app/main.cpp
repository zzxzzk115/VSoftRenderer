//
// main.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:50.
//

#include "VSoftRenderer/Extern.h"
#include "VSoftRenderer/Line.h"
#include "VSoftRenderer/RenderConfig.h"
#include "VSoftRenderer/Triangle.h"

#include <raylib-cpp.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <iostream>

// implement extern VDrawPixel funtion by using Raylib
void VDrawPixel(int x, int y, const VSoftRenderer::Color& color)
{
    Color rayColor{color.R, color.G, color.B, color.A};
    DrawPixel(x, y, rayColor);
}

const int ScreenWidth = 800;
const int ScreenHeight = 800;

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
                VSoftRenderer::Vector2Int* screenCoords = new VSoftRenderer::Vector2Int[3];
                for (size_t v = 0; v < fv; v++)
                {
                    auto index = shapes[s].mesh.indices[indexOffset + v];

                    float x = attrib.vertices[3*size_t(index.vertex_index)+0];
                    float y = attrib.vertices[3*size_t(index.vertex_index)+1];

                    screenCoords[v] = {static_cast<int>((x+1.0f)*ScreenWidth/2.0f), static_cast<int>((y+1.0f)*ScreenHeight/2.0f)};
                }
                VSoftRenderer::Triangle::DrawFilled(screenCoords[0],
                                                    screenCoords[1],
                                                    screenCoords[2],
                                                    {
                                                        static_cast<unsigned char>(rand()%255),
                                                        static_cast<unsigned char>(rand()%255),
                                                        static_cast<unsigned char>(rand()%255),
                                                        255});
                delete(screenCoords);
                screenCoords = nullptr;
                indexOffset += fv;
            }
        }

            // VSoftRenderer::Triangle::DrawFilled({10,10}, {100, 30}, {190, 160}, VSoftRenderer::Color::COLOR_RED);
        renderTexture.EndMode();

        BeginDrawing();
            window.ClearBackground(BLACK);
            targetTexture.Draw(0, 0);
        EndDrawing();
    }

    return 0;
}