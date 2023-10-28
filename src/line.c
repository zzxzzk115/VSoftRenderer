#include "line.h"

#include <raylib.h>

void VDrawLine(int x0, int y0, int x1, int y1, struct Color color)
{
    for (float t=0; t<1; t+=.01) 
    { 
        int x = x0 + (x1-x0)*t; 
        int y = y0 + (y1-y0)*t; 
        DrawPixel(x, y, color); 
    } 
}