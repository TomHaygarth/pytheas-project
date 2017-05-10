
#include "Paddle.h"
#include<glm/vec3.hpp>
#include "../Graphics/Sprites/ISprite.h"
#include "../Physics2D/IAABBCollider2D.h"

namespace GameComponents
{
	Paddle::Paddle(Graphics::Sprites::ISprite * sprite, const glm::vec3 & position, const float& minXBound, const float& maxXBound)
		: GameObject(sprite, position),
		m_minXBound(minXBound),
		m_maxXBound(maxXBound)
	{

	}
	void Paddle::MoveLeft(const float & deltatime)
	{
		m_position.x -= 640.0f *deltatime;

		if (m_position.x < m_minXBound + (m_sprite->GetSize().x * 0.5f))
		{
			m_position.x = m_minXBound + (m_sprite->GetSize().x * 0.5f);
		}

		m_collider->SetPosition(glm::vec2(m_position));
	}
	void Paddle::MoveRight(const float & deltatime)
	{
		m_position.x += 640.0f *deltatime;

		if (m_position.x > m_maxXBound - (m_sprite->GetSize().x * 0.5f))
		{
			m_position.x = m_maxXBound - (m_sprite->GetSize().x * 0.5f);
		}

		m_collider->SetPosition(glm::vec2(m_position));
	}
}