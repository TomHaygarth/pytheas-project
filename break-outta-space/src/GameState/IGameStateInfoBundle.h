
#pragma once

#include <string>
#include "Engine.h"

namespace Engine
{
	class IGameStateInfoBundle
	{
		virtual const int GetInt(const std::string& propertyName,
								 const int& defaultValue) const = 0;

		virtual const std::string& GetString(const std::string& propertyName,
											 const int& defaultValue) const = 0;
	};
}