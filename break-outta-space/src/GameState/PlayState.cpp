
#include "PlayState.h"
#include "../Input/IInputManager.h"

#include "../Graphics/GraphicalStructs.h"
#include "../Graphics/IGraphicsManager.h"
#include "../Graphics/IShader.h"
#include "../Graphics/Sprites/ISpriteFactory.h"
#include "../Graphics/Sprites/ISprite.h"

#include "../GameComponents/BlockManager.h"
#include "../GameComponents/Paddle.h"
#include "../GameComponents/Ball.h"

#include <SDL_keycode.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>

namespace GameState
{
	PlayState::PlayState(Input::IInputManager & inputManager, Graphics::IGraphicsManager& graphicsManager, Graphics::Sprites::ISpriteFactory& spriteFactory)
		:m_inputManager(inputManager),
		m_graphicsManager(graphicsManager),
		m_spriteFactory(spriteFactory),
		m_backgroundSprite(nullptr),
		m_spriteShader(nullptr),
		m_BlockManager(nullptr),
		m_paddle(nullptr),
		m_ball(nullptr),
		m_lifeCounter(nullptr),
		m_maxLives(3),
		m_currentLives(3),
		m_maxLevels(2),
		m_currentLevel(0)
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

	void PlayState::ResetGame()
	{
		m_currentLives = m_maxLives;
		if(!m_BlockManager->LoadLevel(m_currentLevel))
		{
			std::cout << "Failed to load level: " << m_currentLevel << std::endl;
		}
	}
	void PlayState::LoadNextLevel()
	{
		++m_currentLevel;

		if (m_currentLevel == m_maxLevels)
		{
			m_currentLevel = 0;
		}

		if (!m_BlockManager->LoadLevel(m_currentLevel))
		{
			std::cout << "Failed to load level: " << m_currentLevel << std::endl;
		}
		m_ball->Respawn();
	}
}