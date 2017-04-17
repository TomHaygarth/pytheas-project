
#pragma once

#include "GameState.h"
#include "IGameState.h"

#include "../Input/Input.h"

namespace GameState
{
	class PlayState : public IGameState
	{
	public:

		PlayState(Input::IInputManager& inputManager);

		const int OnInitialise(const IGameStateInfoBundle& stateBundle);
		const int OnResume(const IGameStateInfoBundle& stateBundle);
		const int OnPause(const IGameStateInfoBundle& stateBundle);
		const int OnDestroy();

		void OnUpdate(const unsigned int& deltaTimeMs);
		void OnRenderGame();
		void OnRenderUI();

	private:

		float m_colorR;
		float m_colorG;
		float m_colorB;
		Input::IInputManager& m_inputManager;
	};
}