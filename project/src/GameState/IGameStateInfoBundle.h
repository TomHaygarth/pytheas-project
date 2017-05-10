
#pragma once

#include <string>

namespace GameState
{
	class IGameStateInfoBundle
	{
	public:
		virtual const int GetInt(const std::string& propertyName, const int& defaultValue) const = 0;
		virtual void SetInt(const std::string& propertyName, const int& value) = 0;
	};
}