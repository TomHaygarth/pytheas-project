
#pragma once

#include"IAABBCollider2D.h"
#include <glm/vec2.hpp>

namespace Physics2D
{
	class AABBCollider2D : public IAABBCollider2D
	{
	public:

		AABBCollider2D(const glm::vec2& size);

		const bool CheckAABBCollision(const IAABBCollider2D& collider)const ;
		const glm::vec2& GetMinBound() const { return m_boundsMin; }
		const glm::vec2& GetMaxBound() const { return m_boundsMax; }
		const glm::vec2& GetPosition() const { return m_position; }
		const void SetPosition(glm::vec2& position) { m_position = position; }

	private:
		glm::vec2 m_position;
		glm::vec2 m_boundsMin;
		glm::vec2 m_boundsMax;
	};
}