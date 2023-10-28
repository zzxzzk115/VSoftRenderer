//
// Extern.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 14:56.
//

#pragma once

#include "VSoftRenderer/Color.h"

/**
 * Draw a pixel.
 * It's an external function and the only external thing we need for a software rasterizer.
 * @param x
 * @param y
 * @param color
 */
extern void VDrawPixel(int x, int y, const VSoftRenderer::Color& color);