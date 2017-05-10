
#pragma once

#include <glm/vec2.hpp>

namespace Physics2D
{
	class IAABBCollider2D
	{
	public:
		virtual const bool CheckAABBCollision(const IAABBCollider2D& collider) const =0;
		virtual const glm::vec2& GetMinBound() const = 0;
		virtual const glm::vec2& GetMaxBound() const = 0;
		virtual const glm::vec2& GetPosition() const = 0;
		virtual const void SetPosition(glm::vec2& position) = 0;
	};
}