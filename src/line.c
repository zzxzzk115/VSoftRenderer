#include "line.h"

#include <raylib.h>

void VDrawLine(int x0, int y0, int x1, int y1, struct Color color)
{
    for (int x = x0; x <= x1; ++x) 
    { 
        float t = (float)(x-x0) / (x1-x0); 
        int y = y0 * (1.0f - t) + y1 * t; 
        DrawPixel(x, y, color); 
    } 
}