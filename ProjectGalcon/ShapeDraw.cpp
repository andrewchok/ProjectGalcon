#include <windows.h>											// Header File For Windows

#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "gl/freeglut.h"

#include <math.h>

#include "openGLFramework.h"
#include "baseTypes.h"
#include "ShapeDraw.h"


constexpr float_t DEG2RAD = 3.14159f/180.0f;
const Coord2D CHARACTER_OFFSET = { 6, 8 };

void DrawLine(float_t startX, float_t startY, float_t endX, float_t endY, uchar8_t r, uchar8_t g, uchar8_t b, float_t lineWidth)
{
	glDisable(GL_TEXTURE_2D);
	glColor4ub(r, g, b, 0xFF);

	// Draw filtered lines
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
		glVertex2f(startX, startY);
		glVertex2f(endX, endY);
	glEnd();

}

void DrawTriangle(Coord2D vert1, Coord2D vert2, Coord2D vert3, uchar8_t r, uchar8_t g, uchar8_t b, float_t lineWidth)
{
	DrawLine(vert1.x, vert1.y, vert2.x, vert2.y, r, g, b, lineWidth);
	DrawLine(vert2.x, vert2.y, vert3.x, vert3.y, r, g, b, lineWidth);
	DrawLine(vert3.x, vert3.y, vert1.x, vert1.y, r, g, b, lineWidth);
}

void DrawCircle(float_t radius, float_t x, float_t y, uchar8_t r, uchar8_t g, uchar8_t b, bool8_t filled, float_t lineWidth)
{
	if(!filled)
	{
		glDisable(GL_TEXTURE_2D);
		glColor4ub(r, g, b,0xFF);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		for (int i=0; i < 360; i+=2)
		{
			const float degInRad = i*DEG2RAD;
			glVertex2f(x + (cosf(degInRad)*radius),y + (sinf(degInRad)*radius));
		}
		glEnd();
	}
	else
	{
		// Smoother circle but doesn't work on some monitors
		//glDisable(GL_TEXTURE_2D);
		//glColor4ub(r, g, b,0xFF);
		//glEnable(GL_POINT_SMOOTH);
		//glEnable(GL_BLEND); 
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		//glPointSize(radius*2);
		//glBegin(GL_POINTS);
		//glVertex2f(x, y);
		//glEnd();

		glDisable(GL_TEXTURE_2D);
		glColor4ub(r, g, b, 0xFF);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glLineWidth(lineWidth);
		glBegin(GL_TRIANGLE_FAN);
		for (float i = 0.0f; i < 360; i++)
		{
			const float degInRad = i * DEG2RAD;
			glVertex2f(x + (cosf(degInRad) * radius), y + (sinf(degInRad) * radius));
		}
		glEnd();
	}
}


void DrawString(string_t str, float_t left, float_t top, uint32_t color)
{
	const char* cStr = str.c_str();
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glRasterPos2f(left-(CHARACTER_OFFSET.x*str.length()), top-CHARACTER_OFFSET.y);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)cStr);
}