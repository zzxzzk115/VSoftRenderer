//
// main.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:50.
//

#include "VSoftRenderer/Extern.h"
#include "VSoftRenderer/Line.h"
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

int main() 
{
    int screenWidth = 800;
    int screenHeight = 800;

    raylib::Window window(screenWidth, screenHeight, "VSoftRenderer");
    raylib::RenderTexture2D renderTexture(screenWidth, screenHeight);
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
        exit(1);
    }

    VSoftRenderer::Triangle t0({10, 70}, {50, 160}, {70, 80});
    VSoftRenderer::Triangle t1({180, 50}, {150, 1}, {70, 180});
    VSoftRenderer::Triangle t2({180, 150}, {120, 160}, {130, 180});

    while (!window.ShouldClose())
    {
        renderTexture.BeginMode();
//            VSoftRenderer::Line::Draw(13, 20, 80, 40, VSoftRenderer::Color::COLOR_WHITE);
//            VSoftRenderer::Line::Draw(20, 13, 40, 80, VSoftRenderer::Color::COLOR_RED);
//            VSoftRenderer::Line::Draw(80, 40, 13, 20, VSoftRenderer::Color::COLOR_RED);

//        // Draw Wireframe
//        // Loop over shapes
//        for (size_t s = 0; s < shapes.size(); s++)
//        {
//            // Loop over faces(polygon)
//            size_t indexOffset = 0;
//            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
//            {
//                auto fv = static_cast<size_t>(shapes[s].mesh.num_face_vertices[f]);
//
//                // Loop over vertices in the face.
//                for (size_t v = 0; v < fv; v++)
//                {
//                    auto v0Index = shapes[s].mesh.indices[indexOffset + v];
//                    auto v1Index = shapes[s].mesh.indices[indexOffset + (v+1)%3];
//
//                    auto v0x = attrib.vertices[3*size_t(v0Index.vertex_index)+0];
//                    auto v0y = attrib.vertices[3*size_t(v0Index.vertex_index)+1];
//                    auto v1x = attrib.vertices[3*size_t(v1Index.vertex_index)+0];
//                    auto v1y = attrib.vertices[3*size_t(v1Index.vertex_index)+1];
//
//                    int x0 = (v0x+1.0f)*screenWidth/2.0f;
//                    int y0 = (v0y+1.0f)*screenHeight/2.0f;
//                    int x1 = (v1x+1.0f)*screenWidth/2.0f;
//                    int y1 = (v1y+1.0f)*screenHeight/2.0f;
//
//                    VSoftRenderer::Line::Draw(x0, y0, x1, y1, VSoftRenderer::Color::COLOR_WHITE);
//                }
//                indexOffset += fv;
//            }
//        }

            // Draw triangles by old school method: line sweeping
            t0.DrawWire(VSoftRenderer::Color::COLOR_RED);
            t1.DrawWire(VSoftRenderer::Color::COLOR_WHITE);
            t2.DrawWire(VSoftRenderer::Color::COLOR_GREEN);
        renderTexture.EndMode();

        BeginDrawing();
            window.ClearBackground(BLACK);
            targetTexture.Draw(0, 0);
        EndDrawing();
    }

    return 0;
}