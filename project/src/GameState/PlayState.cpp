
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
#include "../GameComponents/Blackhole.h"

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

		keyInput = { Input::KeyboardInput,  SDLK_SPACE };
		m_inputManager.RegisterKeyBinding("launch", keyInput);

		m_spriteShader = m_graphicsManager.LoadShaders("Resources/Shaders/simpleSpriteVert.glsl", "Resources/Shaders/simpleSpriteFrag.glsl");
		glm::mat4 wvp = m_graphicsManager.GetMVPMatrix();
		m_spriteShader->SetMatrixAttrib("WVP", wvp);

		Graphics::TEXTURE_INFO backgroundTexture = m_graphicsManager.LoadTexture("Resources/Textures/nebula_bg.png", m_spriteShader->GetShaderID());
		m_backgroundSprite = m_spriteFactory.CreateSprite(backgroundTexture, *m_spriteShader, glm::vec2(1280, 720), glm::vec3(640.0f, 360.0f, 0.0f));

        Graphics::TEXTURE_INFO blockTexture = m_graphicsManager.LoadTexture("Resources/Textures/planet_block.png", m_spriteShader->GetShaderID());
        Graphics::TEXTURE_INFO blackholeTexture = m_graphicsManager.LoadTexture("Resources/Textures/blackhole.png", m_spriteShader->GetShaderID());
		m_BlockManager = new GameComponents::BlockManager(m_spriteFactory, blockTexture, blackholeTexture, *m_spriteShader);

		Graphics::TEXTURE_INFO paddleTexture = m_graphicsManager.LoadTexture("Resources/Textures/platform_paddle.png", m_spriteShader->GetShaderID());
		Graphics::Sprites::ISprite* paddleSprite = m_spriteFactory.CreateSprite(paddleTexture, *m_spriteShader, glm::vec2(128, 32), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(0.5f, 0.5f, 1.0f));

		m_paddle = new GameComponents::Paddle(paddleSprite, glm::vec3(640.0f, 688.8f, 0.0f));

		Graphics::TEXTURE_INFO ballTexture = m_graphicsManager.LoadTexture("Resources/Textures/ship.png", m_spriteShader->GetShaderID());
		Graphics::Sprites::ISprite* ballSprite = m_spriteFactory.CreateSprite(ballTexture, *m_spriteShader, glm::vec2(32, 32), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		m_ball = new GameComponents::Ball(ballSprite, glm::vec3(640.0f, 672.8f, 0.0f),16.0f);

		m_lifeCounter = m_spriteFactory.CreateSprite(ballTexture, *m_spriteShader, glm::vec2(32, 32), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		
		if (!m_BlockManager->LoadLevel(0))
		{
			return 1;
		}

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
		if (m_lifeCounter != nullptr)
		{
			delete m_lifeCounter;
			m_lifeCounter = nullptr;
		}

		if (m_ball != nullptr)
		{
			delete m_ball;
			m_ball = nullptr;
		}

		if (m_paddle != nullptr)
		{
			delete m_paddle;
			m_paddle = nullptr;
		}

		if (m_BlockManager != nullptr)
		{
			delete m_BlockManager;
			m_BlockManager = nullptr;
		}

		if (m_backgroundSprite != nullptr)
		{
			delete m_backgroundSprite;
			m_backgroundSprite = nullptr;
		}
		
		if (m_spriteShader != nullptr)
		{
			delete m_spriteShader;
			m_spriteShader = nullptr;
		}

		return 0;
	}

	void PlayState::OnUpdate(const float& deltaTimeS)
	{
		if (m_inputManager.GetKeyDown("left"))
		{
			m_paddle->MoveLeft(deltaTimeS);
		}

		if (m_inputManager.GetKeyDown("right"))
		{
			m_paddle->MoveRight(deltaTimeS);
		}

		if (m_inputManager.GetKeyPressed("launch") && !m_ball->HasLaunched())
		{
			m_ball->LaunchBall();
		}
		
		m_ball->UpdateMovement(deltaTimeS, *m_paddle);

		if (m_ball->HasLaunched())
		{
			m_BlockManager->CheckBlockCollisions(*m_ball);
			GameComponents::BallCollision collision = m_ball->CheckCollision(*m_paddle);

			if (std::get<0>(collision))
			{
				glm::vec2 collisionDiff = std::get<1>(collision);
				m_ball->ReactToCollision(collisionDiff);
				m_ball->ReactToPaddle(*m_paddle);
			}

            auto const & blackholes = m_BlockManager->GetBlackholes();
            for (auto const & blackhole : blackholes)
            {
                glm::vec2 gravity = blackhole->CalculateGravitationalPullOnObject(*m_ball) * deltaTimeS;
                m_ball->ApplyGravityPull(gravity);
            }
		}


		if (m_ball->GetPosition().y > m_graphicsManager.GetScreenSize().y)
		{
			m_ball->Respawn();
			--m_currentLives;
		}

		if (m_currentLives <= 0)
		{
			ResetGame();
		}

		if (m_BlockManager->BlocksLeft() <= 0)
		{
			LoadNextLevel();
		}
	}
	void PlayState::OnRenderGame()
	{
		glm::mat4 wvp = m_graphicsManager.GetMVPMatrix();
		m_spriteShader->SetMatrixAttrib("WVP", wvp);
		m_backgroundSprite->Render();
		m_BlockManager->RenderBlocks();
		m_paddle->Render();
		m_ball->Render();

		const float spacing = 32.0f;
		const float screenWidth = m_graphicsManager.GetScreenSize().x;
		
		for (int i = 0; i < m_currentLives; ++i)
		{
			glm::vec3 lifeCounterPos( screenWidth - (spacing * i) -spacing, spacing, 0.0f);
			m_lifeCounter->SetPosition(lifeCounterPos);
			m_lifeCounter->Render();
		}
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