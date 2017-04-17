
#pragma once

#include "IGameStateInfoBundle.h"

#include <string>
#include <map>

namespace GameState
{
	class GameStateInfoBundle : public IGameStateInfoBundle
	{
	public:
		const int GetInt(const std::string& propertyName, const int& defaultValue) const;
		void SetInt(const std::string& propertyName, const int& value);

	private:
		std::map<std::string, int> m_intMap;
	};
}