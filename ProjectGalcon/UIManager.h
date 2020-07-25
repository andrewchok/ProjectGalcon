#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class UIManagerC
{
public:
	static UIManagerC* GetInstance();
	~UIManagerC() noexcept {};


public:
	void init();
	void render();
	void renderBackground();
	void shutdown();

private:
	static UIManagerC* sInstance;

	GLuint mTitleTextureMap;
	GLuint mBackgroundTextureMap;
	GLuint mPauseTextureMap;
	GLuint mBlueWinTextureMap;
	GLuint mRedWinTextureMap;
	GLuint mBluePercentTextureMap[4];
	GLuint mRedPercentTextureMap[4];

private:
	UIManagerC() noexcept {};
};