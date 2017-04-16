
#pragma once

#include "Engine.h"

namespace Engine
{
	class IGameEngine
	{
	public:
		virtual const int Run() = 0;
	};
}