
#pragma once

#include "GameState.h"

namespace GameState
{
	class IGameState
	{
	public:
		
		virtual const int OnInitialise(const IGameStateInfoBundle& stateBundle) = 0;
		virtual const int OnResume(const IGameStateInfoBundle& stateBundle) = 0;
		virtual const int OnPause(const IGameStateInfoBundle& stateBundle) = 0;
		virtual const int OnDestroy() = 0;
		
		virtual void OnUpdate(const float& deltaTimeS) = 0;
		virtual void OnRenderGame() = 0;
		virtual void OnRenderUI() = 0;
	};
}