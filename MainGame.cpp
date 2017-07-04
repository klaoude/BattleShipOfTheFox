#include "MainGame.h"

#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>

#include <SDL/SDL.h>
#include <KlaoudeEngine/KlaoudeEngine.h>
#include <KlaoudeEngine/Timing.h>
#include <KlaoudeEngine/Errors.h>
#include <KlaoudeEngine/RessourceManager.h>

MainGame::MainGame() :
	m_screenWidth(800),
	m_screenHeight(600),
	m_fps(0),
	m_gameState(GameState::PLAY) {}

MainGame::~MainGame()
{

}

void MainGame::run()
{
	initSystems();
	initLevel();

	gameLoop();
}

void MainGame::initSystems()
{
	KlaoudeEngine::init();

	m_window.create("BattleShipOfTheFox", m_screenWidth, m_screenHeight, 0);
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

	initShaders();

	m_camera.init(m_screenWidth, m_screenHeight);

	m_batch.init();
}

void MainGame::initLevel()
{
	m_level = new Level();
}

void MainGame::initShaders()
{
	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();
}

void MainGame::gameLoop()
{
	const float DESIRED_FPS = 60.0f;
	const int MAX_PHYSICS_STEPS = 5;

	KlaoudeEngine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(1337.0f);

	const float MS_PER_SEC = 1000.0f;
	const float DESIRED_FRAMETIME = MS_PER_SEC / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.0f;

	float previousTicks = SDL_GetTicks();

	while (m_gameState == GameState::PLAY)
	{
		fpsLimiter.begin();

		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - previousTicks;
		previousTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

		m_inputManager.update();

		processInput();

		int i = 0;
		while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
		{
			float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
			totalDeltaTime -= deltaTime;
			i++;
		}

		m_camera.update();

		drawGame();

		m_fps = fpsLimiter.end();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);

	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//SpriteBatch Begin
	m_batch.begin();

	//SpriteBatch Draw
	m_level->draw(m_batch);

	//SpriteBatch End
	m_batch.end();

	//SpriteBatch Render
	m_batch.renderBatch();

	m_textureProgram.unUse();

	m_window.swapBuffer();
}