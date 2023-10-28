#include "raylib.h"

int main(void)
{
    InitWindow(1024, 768, "VSoftRenderer");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            
            // get render width and height
            int frameBufferWidth = GetRenderWidth();
            int frameBufferHeight = GetRenderHeight();

            // example: draw an ugly line from top-left to bottom-right
            float k = (float)frameBufferHeight / frameBufferWidth;
            for (int x = 0; x < frameBufferWidth; ++x)
            {
                int y = k * x;
                DrawPixel(x, y, WHITE);
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}