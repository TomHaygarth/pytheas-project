
#pragma once

#include "IBlock.h"
#include "GameObject.h"

#include <glm/vec3.hpp>

namespace GameComponents
{
	class Block : public GameObject, public IBlock
	{
	public:
		Block(Graphics::Sprites::ISprite* sprite, const glm::vec3& position, const int& strength);
		const int& Strength() const { return m_strength; }
		const bool& Destroyed() const { return m_isDestroyed; }
		void Damage();

	private:
		int m_strength;
		int m_remainingHits;
		bool m_isDestroyed;
		glm::vec3 m_originalColour;
	};
}