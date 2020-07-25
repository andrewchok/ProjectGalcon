#define UIMANAGER_CPP

#include "UIManager.h"

#include "SOIL.h"

#include "game.h"
#include "StateManager.h"
#include "PlayerManager.h"


UIManagerC* UIManagerC::sInstance = nullptr;


UIManagerC* UIManagerC::GetInstance()
{
	if (sInstance == nullptr) sInstance = new UIManagerC();
	return sInstance;
}

void UIManagerC::init()
{
	mTitleTextureMap = SOIL_load_OGL_texture("Sprites/Title.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mBackgroundTextureMap = SOIL_load_OGL_texture("Sprites/Background.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mPauseTextureMap = SOIL_load_OGL_texture("Sprites/Pause.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mBlueWinTextureMap = SOIL_load_OGL_texture("Sprites/BlueWin.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mRedWinTextureMap = SOIL_load_OGL_texture("Sprites/RedWin.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mBluePercentTextureMap[0] = SOIL_load_OGL_texture("Sprites/blue25.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mBluePercentTextureMap[1] = SOIL_load_OGL_texture("Sprites/blue50.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mBluePercentTextureMap[2] = SOIL_load_OGL_texture("Sprites/blue75.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mBluePercentTextureMap[3] = SOIL_load_OGL_texture("Sprites/blue100.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mRedPercentTextureMap[0] = SOIL_load_OGL_texture("Sprites/red25.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mRedPercentTextureMap[1] = SOIL_load_OGL_texture("Sprites/red50.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mRedPercentTextureMap[2] = SOIL_load_OGL_texture("Sprites/red75.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mRedPercentTextureMap[3] = SOIL_load_OGL_texture("Sprites/red100.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

void UIManagerC::render()
{
	StateManagerC* stateManager = StateManagerC::GetInstance();
	StateManagerC::State state = stateManager->getState();
	StateManagerC::Winner winner = stateManager->getWinner();

	PlayerManagerC* playerManager = PlayerManagerC::GetInstance();

	glEnable(GL_TEXTURE_2D);

	switch (state)
	{

	case StateManagerC::State::MENU:
		glBindTexture(GL_TEXTURE_2D, mTitleTextureMap);
		glBegin(GL_QUADS);
		glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

		glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);

		glTexCoord2f(1, 0);
		glVertex3f(CGame::SCREEN_WIDTH, 0, 0);

		glTexCoord2f(1, 1);
		glVertex3f(CGame::SCREEN_WIDTH, CGame::SCREEN_HEIGHT, 0);

		glTexCoord2f(0, 1);
		glVertex3f(0, CGame::SCREEN_HEIGHT, 0);

		glEnd();
		break;

	case StateManagerC::State::RUNNING:
		
		// Player One Percentage

		glBindTexture(GL_TEXTURE_2D, mBluePercentTextureMap[(playerManager->getPlayerPercentageSelect(0) / 25)-1]);
		glBegin(GL_QUADS);
		glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

		glTexCoord2f(0, 0);
		glVertex3f(0, CGame::SCREEN_HEIGHT - 50, 0);

		glTexCoord2f(1, 0);
		glVertex3f(500, CGame::SCREEN_HEIGHT - 50, 0);

		glTexCoord2f(1, 1);
		glVertex3f(500, CGame::SCREEN_HEIGHT, 0);

		glTexCoord2f(0, 1);
		glVertex3f(0, CGame::SCREEN_HEIGHT, 0);

		glEnd();

		// Player Two Percentage

		glBindTexture(GL_TEXTURE_2D, mRedPercentTextureMap[(playerManager->getPlayerPercentageSelect(1) / 25) - 1]);
		glBegin(GL_QUADS);
		glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

		glTexCoord2f(0, 0);
		glVertex3f(CGame::SCREEN_WIDTH - 500, CGame::SCREEN_HEIGHT - 50, 0);

		glTexCoord2f(1, 0);
		glVertex3f(CGame::SCREEN_WIDTH, CGame::SCREEN_HEIGHT - 50, 0);

		glTexCoord2f(1, 1);
		glVertex3f(CGame::SCREEN_WIDTH, CGame::SCREEN_HEIGHT, 0);

		glTexCoord2f(0, 1);
		glVertex3f(CGame::SCREEN_WIDTH - 500, CGame::SCREEN_HEIGHT, 0);
		
		glEnd();
		break;

	case StateManagerC::State::PAUSED:
		glBindTexture(GL_TEXTURE_2D, mPauseTextureMap);
		glBegin(GL_QUADS);
		glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

		glTexCoord2f(0, 0);
		glVertex3f((CGame::SCREEN_WIDTH / 2.0f) - 450, (CGame::SCREEN_HEIGHT / 2.0f) - 225, 0);

		glTexCoord2f(1, 0);
		glVertex3f((CGame::SCREEN_WIDTH/2.0f) + 450, (CGame::SCREEN_HEIGHT / 2.0f) - 225, 0);

		glTexCoord2f(1, 1);
		glVertex3f((CGame::SCREEN_WIDTH / 2.0f) + 450, (CGame::SCREEN_HEIGHT/2.0f) + 225, 0);

		glTexCoord2f(0, 1);
		glVertex3f((CGame::SCREEN_WIDTH / 2.0f) - 450, (CGame::SCREEN_HEIGHT / 2.0f) + 225, 0);

		glEnd();
		break;

	case StateManagerC::State::GAME_OVER:		
		if (winner == StateManagerC::Winner::PLAYER_ONE)
			glBindTexture(GL_TEXTURE_2D, mBlueWinTextureMap);
		else if (winner == StateManagerC::Winner::PLAYER_TWO)
			glBindTexture(GL_TEXTURE_2D, mRedWinTextureMap);
		else
			break;

		glBegin(GL_QUADS);
		glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

		glTexCoord2f(0, 0);
		glVertex3f((CGame::SCREEN_WIDTH / 2.0f) - 450, (CGame::SCREEN_HEIGHT / 2.0f) - 225, 0);

		glTexCoord2f(1, 0);
		glVertex3f((CGame::SCREEN_WIDTH / 2.0f) + 450, (CGame::SCREEN_HEIGHT / 2.0f) - 225, 0);

		glTexCoord2f(1, 1);
		glVertex3f((CGame::SCREEN_WIDTH / 2.0f) + 450, (CGame::SCREEN_HEIGHT / 2.0f) + 225, 0);

		glTexCoord2f(0, 1);
		glVertex3f((CGame::SCREEN_WIDTH / 2.0f) - 450, (CGame::SCREEN_HEIGHT / 2.0f) + 225, 0);

		glEnd();
		break;

	default:
		break;
	}

}

void UIManagerC::renderBackground()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mBackgroundTextureMap);
	glBegin(GL_QUADS);
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(CGame::SCREEN_WIDTH, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(CGame::SCREEN_WIDTH, CGame::SCREEN_HEIGHT, 0);

	glTexCoord2f(0, 1);
	glVertex3f(0, CGame::SCREEN_HEIGHT, 0);

	glEnd();
}

void UIManagerC::shutdown()
{
}
