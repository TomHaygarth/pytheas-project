
#include "AABBCollider2D.h"

namespace Physics2D
{

	AABBCollider2D::AABBCollider2D(const glm::vec2 & size)
	{
		m_boundsMax.x = (size.x * 0.5f);
		m_boundsMax.y = (size.y * 0.5f);

		m_boundsMin = -m_boundsMax;
	}

	const bool AABBCollider2D::CheckAABBCollision(const IAABBCollider2D & collider) const
	{
		glm::vec2 otherMin = collider.GetMinBound() + collider.GetPosition();
		glm::vec2 otherMax = collider.GetMaxBound() + collider.GetPosition();

		if (otherMax.x >= m_boundsMin.x + m_position.x &&
			otherMax.y >= m_boundsMin.y + m_position.y &&
			otherMin.x <= m_boundsMax.x + m_position.x &&
			otherMin.y <= m_boundsMax.y + m_position.y)
		{
			return true;
		}
		return false;
	}
}