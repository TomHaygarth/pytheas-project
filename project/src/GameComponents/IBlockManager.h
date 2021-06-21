
#pragma once

#include "GameComponents.h"
#include <vector>

namespace GameComponents
{
	class IBlockManager
	{
	public:
        virtual ~IBlockManager() {};
		virtual bool LoadLevel(const int& level) = 0;
		virtual void CheckBlockCollisions(Ball& ball) = 0;
		virtual void RenderBlocks() const = 0;
		virtual const int& BlocksLeft() const = 0;

        virtual std::vector<Blackhole *> const & GetBlackholes() const = 0;
	};
}