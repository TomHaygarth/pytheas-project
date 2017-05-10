
#pragma once

#include "GameComponents.h"

namespace GameComponents
{
	class IBlockManager
	{
	public:
		virtual bool LoadLevel(const int& level) = 0;
		virtual void CheckBlockCollisions(Ball& ball) = 0;
		virtual void RenderBlocks() const = 0;
		virtual const int& BlocksLeft() const = 0;
	};
}