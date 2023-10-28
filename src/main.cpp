#include "VSoftRenderer/VLine.h"

#include <raylib-cpp.hpp>

using namespace VSoftRenderer;

int main() 
{
    int screenWidth = 1024;
    int screenHeight = 768;

    raylib::Window window(screenWidth, screenHeight, "VSoftRenderer");
    raylib::RenderTexture2D renderTexture(screenWidth, screenHeight);
    raylib::Texture targetTexture(renderTexture.GetTexture());

    SetTargetFPS(60);

    VLine line1(13, 20, 80, 40, WHITE);
    VLine line2(20, 13, 40, 80, RED);
    VLine line3(80, 40, 13, 20, RED);

    while (!window.ShouldClose())
    {
        renderTexture.BeginMode();
            line1.Draw();
            line2.Draw();
            line3.Draw();
        renderTexture.EndMode();

        BeginDrawing();
            window.ClearBackground(BLACK);
            targetTexture.Draw(0, 0);
        EndDrawing();
    }

    return 0;
}