#include "GameEngine.h"
#include "../GameState/IGameState.h"
#include "../GameState/PlayState.h"
#include "../GameState/GameStateInfoBundle.h"

#include "../Input/InputManager.h"

#include "../Graphics/GraphicsManager.h"
#include "../Graphics/Sprites/SpriteFactory.h"

#include <iostream>
#include <GL/glew.h>
#include <stdlib.h>
#include <time.h>

namespace Engine
{
	GameEngine::GameEngine(void)
	{
		m_currentGameState = nullptr;
		m_sdlWindow = nullptr;
		m_inputManager = nullptr;
		m_graphicsManager = nullptr;
		m_spriteFactory = nullptr;
		m_quitGame = false;
	}


	GameEngine::~GameEngine()
	{
	}

	const int GameEngine::Run()
	{

		bool initSuccess = Initialise();
		int errorCode = 0;

		glBindVertexArray(0);

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
				case SDL_MOUSEBUTTONDOWN:
				case SDL_KEYUP:
				case SDL_MOUSEBUTTONUP:
					m_inputManager->UpdateKeys(e);
					break;


				default:
					break;
				}
			}

			glClearColor(0.0, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBindVertexArray(mVertexArray);

			if (m_currentGameState != nullptr)
			{
				const Uint32 currentTick = SDL_GetTicks();
				const float msToS = 1.0f / 1000.0f;
				const float deltaTime = static_cast<float>(currentTick - m_prevTickCount) * msToS;

				m_currentGameState->OnUpdate(deltaTime);
				m_prevTickCount = currentTick;
				m_inputManager->Update();

				m_currentGameState->OnRenderGame();

				m_currentGameState->OnRenderUI();
				
			}
			glBindVertexArray(0);
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

		const int screenWidth = 1280;
		const int screenHeight = 720;

		m_sdlWindow = SDL_CreateWindow("Break outta space",
									   SDL_WINDOWPOS_CENTERED,
									   SDL_WINDOWPOS_CENTERED,
									   screenWidth,
									   screenHeight,
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

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LESS);

		glGenVertexArrays(1, &mVertexArray);
		glBindVertexArray(mVertexArray);

		srand(static_cast<unsigned int>(time(NULL)));

		m_inputManager = new Input::InputManager(*m_sdlWindow);
		
		m_graphicsManager = new Graphics::GraphicsManager(static_cast<float>(screenWidth), static_cast<float>(screenHeight), m_sdlWindow);

		m_spriteFactory = new Graphics::Sprites::SpriteFactory();

		m_currentGameState = new GameState::PlayState(*m_inputManager, *m_graphicsManager, *m_spriteFactory);

		glBindVertexArray(0);

		if (!InitialiseFistGameState())
		{
			CleanUp();
			return false;
		}

		return true;
		
	}

	const bool GameEngine::InitialiseFistGameState()
	{
		GameState::GameStateInfoBundle stateBundle;
		stateBundle.SetInt("highscore", 100);

		if (m_currentGameState->OnInitialise(stateBundle) != 0)
		{
			std::cout << "Failed to initialize game state" << std::endl;
			return false;
		}

		return true;
	}

	void GameEngine::CleanUp()
	{
		glDeleteVertexArrays(1, &mVertexArray);

		if (m_currentGameState != nullptr)
		{
			m_currentGameState->OnDestroy();
			delete m_currentGameState;
			m_currentGameState = nullptr;
		}

		if (m_spriteFactory != nullptr)
		{
			delete m_spriteFactory;
			m_spriteFactory = nullptr;
		}

		if (m_graphicsManager != nullptr)
		{
			delete m_graphicsManager;
			m_graphicsManager = nullptr;
		}

		if (m_inputManager != nullptr)
		{
			delete m_inputManager;
			m_inputManager = nullptr;
		}

		SDL_GL_DeleteContext(m_sdlGLContext);

		SDL_DestroyWindow(m_sdlWindow);

		SDL_Quit();
	}
}