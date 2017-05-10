
#include "GameStateInfoBundle.h"

namespace GameState
{
	const int GameStateInfoBundle::GetInt(const std::string & propertyName, const int & defaultValue) const
	{
		std::map<std::string, int>::const_iterator it = m_intMap.find(propertyName);

		if (it == m_intMap.end())
		{
			return defaultValue;
		}

		return it->second;
	}

	void GameStateInfoBundle::SetInt(const std::string & propertyName, const int & value)
	{
		m_intMap[propertyName] = value;
	}
}