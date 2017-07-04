#pragma once

#include <memory>

#include "KlaoudeEngine.h"
#include "InputManager.h"
#include "Window.h"

namespace KlaoudeEngine
{
	class ScreenList;
	class IGameScreen;

	class IMainGame
	{
	public:
		IMainGame();
		virtual ~IMainGame();

		void run(std::string windowName, int screenWidth, int screenHeight);
		void exitGame();		

		virtual void onInit() = 0;
		virtual void addScreens() = 0;
		virtual void onExit() = 0;		

		void onSDLEvent(SDL_Event& evnt);

		const float getFps() const { return m_fps; }

		InputManager inputManager;

	protected:
		virtual void update();
		virtual void draw();		

		bool init(std::string windowName, int screenWidth, int screenHeight);
		bool initSystems(std::string windowName, int screenWidth, int screenHeight);

		std::unique_ptr<ScreenList> m_screenList = nullptr;
		IGameScreen* m_currentScreen = nullptr;
		bool m_isRunning = false;
		float m_fps = 0.0f;
		Window m_window;
	};
}