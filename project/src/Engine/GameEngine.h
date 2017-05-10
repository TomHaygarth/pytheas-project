
#pragma once
#include "Engine.h"
#include "../GameState/GameState.h"
#include "../Graphics/Graphics.h"
#include "../Input/Input.h"
#include "IGameEngine.h"
#include <SDL.h>
#include <GL/glew.h>

namespace Engine
{
	class GameEngine : public IGameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		const int Run();

	private:

		const bool Initialise();
		const bool InitialiseFistGameState();

		void CleanUp();

		bool m_quitGame;
		Uint32 m_prevTickCount;

		SDL_Window* m_sdlWindow;
		SDL_GLContext m_sdlGLContext;
		GLuint mVertexArray;

		GameState::IGameState* m_currentGameState;
		Input::IInputManager* m_inputManager;
		Graphics::IGraphicsManager* m_graphicsManager;
		Graphics::Sprites::ISpriteFactory* m_spriteFactory;
	};
}