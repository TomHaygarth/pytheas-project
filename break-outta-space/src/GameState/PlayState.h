
#pragma once

#include "GameState.h"
#include "IGameState.h"

#include "../Graphics/Graphics.h"
#include "../Input/Input.h"
#include "../GameComponents/GameComponents.h"

namespace GameState
{
	class PlayState : public IGameState
	{
	public:

		PlayState(Input::IInputManager& inputManager, Graphics::IGraphicsManager& graphicsManager, Graphics::Sprites::ISpriteFactory& spriteFactory);

		const int OnInitialise(const IGameStateInfoBundle& stateBundle);
		const int OnResume(const IGameStateInfoBundle& stateBundle);
		const int OnPause(const IGameStateInfoBundle& stateBundle);
		const int OnDestroy();

		void OnUpdate(const float& deltaTimeS);
		void OnRenderGame();
		void OnRenderUI();

	private:

		void ResetGame();
		void LoadNextLevel();

		Input::IInputManager& m_inputManager;
		Graphics::IGraphicsManager& m_graphicsManager;

		Graphics::Sprites::ISpriteFactory& m_spriteFactory;
		Graphics::Sprites::ISprite* m_backgroundSprite;
		Graphics::IShader* m_spriteShader;

		GameComponents::IBlockManager* m_BlockManager;
		GameComponents::Ball* m_ball;
		GameComponents::Paddle* m_paddle;

		Graphics::Sprites::ISprite* m_lifeCounter;
		const int m_maxLives;
		int m_currentLives;
		const int m_maxLevels;
		int m_currentLevel;
	};
}