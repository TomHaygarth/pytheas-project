
#pragma once
#include "IGameObject.h"
#include "../Graphics/Graphics.h"
#include "../Physics2D/Physics2D.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace GameComponents
{
	class GameObject : public IGameObject
	{
	public:
		GameObject(Graphics::Sprites::ISprite* sprite, const glm::vec3& position);
		virtual ~GameObject();
		
		void SetPosition(const glm::vec3& position) { m_position = position; }
		const glm::vec3& GetPosition() const { return m_position; }
		const glm::vec2& GetSize() const { return m_size; }
		const Physics2D::IAABBCollider2D& GetAABBColider() const { return *m_collider; };
		
		void Render() const;

	protected:
		glm::vec3 m_position;
		glm::vec2 m_size;
		Graphics::Sprites::ISprite* m_sprite;

		Physics2D::IAABBCollider2D* m_collider;
	};
}