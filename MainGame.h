#pragma once

#include <KlaoudeEngine/Window.h>
#include <KlaoudeEngine/GLSLProgram.h>
#include <KlaoudeEngine/Camera2D.h>
#include <KlaoudeEngine/InputManager.h>
#include <KlaoudeEngine/SpriteBatch.h>
#include <KlaoudeEngine/SpriteFont.h>
#include <KlaoudeEngine/AudioEngine.h>
#include <KlaoudeEngine/ParticleEngine2D.h>

#include "Level.h"

enum class GameState
{
	PLAY,
	EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initLevel();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	KlaoudeEngine::Window m_window;
	KlaoudeEngine::GLSLProgram m_textureProgram;
	KlaoudeEngine::InputManager m_inputManager;
	KlaoudeEngine::Camera2D m_camera;
	KlaoudeEngine::SpriteBatch m_batch;

	int m_screenWidth, m_screenHeight;
	float m_fps;

	GameState m_gameState;

	Level* m_level;
};