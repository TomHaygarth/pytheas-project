
#include "PlayState.h"
#include "../Input/IInputManager.h"

#include <SDL_keycode.h>
#include<GL\glew.h>

namespace GameState
{
	PlayState::PlayState(Input::IInputManager & inputManager)
		:m_inputManager(inputManager)
	{

	}

	const int PlayState::OnInitialise(const IGameStateInfoBundle & stateBundle)
	{
		Input::InputControl keyInput = { Input::KeyboardInput,  SDLK_LEFT};
		m_inputManager.RegisterKeyBinding("left", keyInput);

		keyInput = { Input::KeyboardInput,  SDLK_RIGHT };
		m_inputManager.RegisterKeyBinding("right", keyInput);

		m_colorR = 0.0f;
		m_colorG = 0.0f;
		m_colorB = 0.0f;

		return 0;
	}

	const int PlayState::OnResume(const IGameStateInfoBundle & stateBundle)
	{
		return 0;
	}

	const int PlayState::OnPause(const IGameStateInfoBundle & stateBundle)
	{
		return 0;
	}

	const int PlayState::OnDestroy()
	{
		return 0;
	}

	void PlayState::OnUpdate(const float& deltaTimeS)
	{
		if (m_inputManager.GetKeyPressed("left"))
		{
			m_colorR = 1.0f;
		}
		else if (m_inputManager.GetKeyReleased("left"))
		{
			m_colorR = 0;
		}

		if (m_inputManager.GetKeyPressed("right"))
		{
			m_colorG = 1.0f;
		}
		else if (m_inputManager.GetKeyReleased("right"))
		{
			m_colorG = 0;
		}
	}
	void PlayState::OnRenderGame()
	{
		glClearColor(m_colorR, m_colorG, m_colorB, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void PlayState::OnRenderUI()
	{
	}
}