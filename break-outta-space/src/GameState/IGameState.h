
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
		
		virtual void OnUpdate(const uint32_t& deltaTimeMs) = 0;
		virtual void OnRenderGame() = 0;
		virtual void OnRenderUI() = 0;
	};
}