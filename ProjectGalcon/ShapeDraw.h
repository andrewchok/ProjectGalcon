#ifndef SHAPEDRAW_H
#define SHAPEDRAW_H

#include "baseTypes.h"

void DrawLine(float_t startX, float_t startY, float_t endX, float_t endY, uchar8_t r, uchar8_t g, uchar8_t b, float_t lineWidth = 1.0f);
void DrawTriangle(Coord2D vert1, Coord2D vert2, Coord2D vert3, uchar8_t r, uchar8_t g, uchar8_t b, float_t lineWidth = 3.0f);
void DrawCircle(float_t radius, float_t x, float_t y, uchar8_t r, uchar8_t g, uchar8_t b, bool8_t filled, float_t lineWidth = 1.0f);

void DrawString(string_t str, float_t left, float_t top, uint32_t color);

#endif // !SHAPEDRAW_H

