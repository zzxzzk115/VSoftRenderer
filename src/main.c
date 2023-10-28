#include "line.h"

#include <raylib.h>

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

            // Attempt 1:
            VDrawLine(0, 0, frameBufferWidth - 1, frameBufferHeight - 1, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}