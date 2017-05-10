
#pragma once

namespace GameComponents
{
	class IBlock
	{
	public:
		virtual const int& Strength() const = 0;
		virtual const bool& Destroyed() const = 0;
		virtual void Damage() = 0;
	};
}