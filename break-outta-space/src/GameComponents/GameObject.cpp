
#include "GameObject.h"
#include "../Graphics/Sprites/ISprite.h"
#include "../Physics2D/AABBCollider2D.h"

namespace GameComponents
{
	GameObject::GameObject(Graphics::Sprites::ISprite * sprite, const glm::vec3& position)
		: m_sprite(sprite),
		m_position(position),
		m_collider(nullptr)
	{
		m_size = m_sprite->GetSize();
		m_collider = new Physics2D::AABBCollider2D(m_size);
		m_sprite->SetPosition(position);
		m_collider->SetPosition(glm::vec2(position.x, position.y));

	}
	GameObject::~GameObject()
	{
		delete m_sprite;

		if (m_collider != nullptr)
		{
			delete m_collider;
			m_collider = nullptr;
		}
	}
	void GameObject::Render() const
	{
		m_sprite->SetPosition(m_position);
		m_sprite->Render();
	}
}