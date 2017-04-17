
#pragma once
#include "Engine.h"
#include "../GameState/GameState.h"
#include "../Input/Input.h"
#include "IGameEngine.h"
#include <SDL.h>

namespace Engine
{
	class GameEngine : public IGameEngine
	{
	public:
		GameEngine(void);
		~GameEngine(void);

		const int Run();

	private:

		const bool Initialise();
		const bool InitialiseFistGameState();

		void CleanUp();

		bool m_quitGame;
		Uint32 m_prevTickCount;

		SDL_Window* m_sdlWindow;
		SDL_GLContext m_sdlGLContext;

		GameState::IGameState* m_currentGameState;
		Input::IInputManager* m_inputManager;
	};
}