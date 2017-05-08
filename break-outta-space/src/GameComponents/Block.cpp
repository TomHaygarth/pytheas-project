
#include "Block.h"

#include "../Graphics/Sprites/ISprite.h"

namespace GameComponents
{
	Block::Block(Graphics::Sprites::ISprite * sprite, const glm::vec3 & position, const int & strength)
		: GameObject(sprite, position),
		m_strength(strength),
		m_remainingHits(strength),
		m_isDestroyed(false)
	{
		if (strength <= 0)
		{
			m_strength = m_remainingHits = 1;
		}

		m_originalColour = m_sprite->GetColor();
	}
	void Block::Damage()
	{
		--m_remainingHits;
		if (m_remainingHits > 0)
		{
			const float healthPercentage = static_cast<float>(m_remainingHits) / static_cast<float>(m_strength);

			m_sprite->SetColor(m_originalColour * healthPercentage);
		}
		else
		{
			m_isDestroyed = true;
		}
	}
}