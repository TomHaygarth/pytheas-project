#include "GameEngine.h"
#include "../GameState/IGameState.h"

#include <iostream>
#include <GL/glew.h>

namespace Engine
{
	GameEngine::GameEngine(void)
	{
		m_currentGameState = nullptr;
		m_sdlWindow = nullptr;
		m_inputManager = nullptr;
		m_quitGame = false;
	}


	GameEngine::~GameEngine(void)
	{
	}

	const int GameEngine::Run()
	{
		bool initSuccess = Initialise();
		int errorCode = 0;

		if (!initSuccess)
		{
			errorCode = 1;
			return errorCode;
		}

		m_prevTickCount = SDL_GetTicks();

		SDL_Event e;
		while (!m_quitGame)
		{
			while (SDL_PollEvent(&e))
			{
				switch (static_cast<SDL_EventType>(e.type))
				{
				case SDL_QUIT:
					m_quitGame = true;
					break;
				
				case SDL_KEYDOWN:
					m_quitGame = true;
					break;
				
				case SDL_MOUSEBUTTONDOWN:
					break;

				case SDLK_0:

				default:
					break;
				}
			}

			if (m_currentGameState != nullptr)
			{
				const Uint32 currentTick = SDL_GetTicks();
				m_currentGameState->OnUpdate(currentTick - m_prevTickCount);
				m_prevTickCount = currentTick;

				glPushMatrix();
				m_currentGameState->OnRenderGame();
				glPopMatrix();

				m_currentGameState->OnRenderUI();
				
			}
			glClearColor(0.0, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_GL_SwapWindow(m_sdlWindow);
		}

		CleanUp();

		return errorCode;
	}

	const bool GameEngine::Initialise()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		{
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return false;
		}

		m_sdlWindow = SDL_CreateWindow("Break outta space",
									   SDL_WINDOWPOS_CENTERED,
									   SDL_WINDOWPOS_CENTERED,
									   640,
									   480,
									   SDL_WINDOW_OPENGL);
		if (m_sdlWindow == nullptr)
		{
			std::cout << "SDL_CreateWindow  Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		m_sdlGLContext = SDL_GL_CreateContext(m_sdlWindow);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
			CleanUp();
			return false;
		}

		return true;
	}

	void GameEngine::CleanUp()
	{
		SDL_GL_DeleteContext(m_sdlGLContext);

		SDL_DestroyWindow(m_sdlWindow);

		SDL_Quit();
	}
}