
#include "Ball.h"
#include "Paddle.h"
#include "../Physics2D/IAABBCollider2D.h"
#include <math.h>

namespace GameComponents
{
	Ball::Ball(Graphics::Sprites::ISprite * sprite, const glm::vec3 & position, const float& collisionRadius, const glm::vec2& minBounds, const glm::vec2& maxBounds)
		: GameObject(sprite, position),
		m_collisionRadius(collisionRadius),
		m_minBounds(minBounds),
		m_maxBounds(maxBounds),
		m_initialBallVelocity(150.0f, -350.0f)
	{
		Respawn();
	}
	void Ball::Respawn()
	{
		m_isStuck = true;
		m_velocity = m_initialBallVelocity;
	}

	void Ball::UpdateMovement(const float & deltaTimeS, const Paddle & paddle)
	{
		glm::vec2 sizeExtents = m_sprite->GetSize() * 0.5f;

		if (!m_isStuck)
		{
			m_position.x += m_velocity.x * deltaTimeS;
			m_position.y += m_velocity.y * deltaTimeS;

			if ((m_position.x  - sizeExtents.x) <= m_minBounds.x)
			{
				m_velocity.x *= -1.0f;
				m_position.x = sizeExtents.x;
			}
			else if ((m_position.x + sizeExtents.x) >= m_maxBounds.x)
			{
				m_velocity.x *= -1.0f;
				m_position.x = m_maxBounds.x - sizeExtents.x;
			}

			if ((m_position.y - sizeExtents.y) <= m_minBounds.y)
			{
				m_velocity.y *= -1.0f;
				m_position.y = sizeExtents.y;
			}
		}
		else
		{
			glm::vec3 paddlePos = paddle.GetPosition();
			glm::vec2 paddleExtents = paddle.GetAABBColider().GetMaxBound();

			m_position.x = paddlePos.x;
			m_position.y = paddlePos.y - paddleExtents.y - sizeExtents.y;
		}

		m_collider->SetPosition(glm::vec2(m_position.x, m_position.y));

		glm::vec2 velocityNorm = glm::normalize(m_velocity);
		float angle = atan2f(0.0f, -1.0f) - atan2(velocityNorm.x, velocityNorm.y);
		if (angle < 0.0f)
		{
			angle += 2.0f * 3.14159f;
		}

		m_sprite->SetRotation(angle);

	}
	BallCollision Ball::CheckCollision(const GameObject& object) const
	{
		const glm::vec2 objectPos = glm::vec2(object.GetPosition());
		const glm::vec2 myPos = glm::vec2(m_position);
		glm::vec2 diff = myPos - objectPos;
		const glm::vec2 clamped = glm::clamp(diff, object.GetAABBColider().GetMinBound(), object.GetAABBColider().GetMaxBound());
		const glm::vec2 closest = objectPos + clamped;
		diff = closest - myPos;

		if (glm::length(diff) < m_collisionRadius)
		{
			return std::make_tuple(true, diff);
		}

		return std::make_tuple(false, glm::vec2(0.0f,0.0f));
	}
	
	void Ball::ReactToCollision(const glm::vec2 & collisionDiff)
	{
		Direction direction = CollisionDirection(collisionDiff);
		if (direction == LEFT || direction == RIGHT)
		{
			m_velocity.x *= -1.0f;
			float penetration = m_collisionRadius - std::abs(collisionDiff.x);
			if (direction == LEFT)
				m_position.x += penetration;
			else
				m_position.x -= penetration;
		}
		else
		{
			m_velocity.y *= -1.0f; 
			float penetration = m_collisionRadius - std::abs(collisionDiff.y);
			if (direction == UP)
				m_position.y -= penetration;
			else
				m_position.y += penetration;
		}
	}

	void Ball::ReactToPaddle(const Paddle& paddle)
	{
		const float distance = m_position.x - paddle.GetPosition().x;
		const float percent = distance / (paddle.GetSize().x * 0.5f);
		const float maxForce = 2.0f;
		m_velocity.x = m_initialBallVelocity.x * percent* maxForce;

	}

	Ball::Direction  Ball::CollisionDirection(const glm::vec2& collisionDiff)
	{
		glm::vec2 compass[] = {
			glm::vec2(0.0f, 1.0f),	// up
			glm::vec2(1.0f, 0.0f),	// right
			glm::vec2(0.0f, -1.0f),	// down
			glm::vec2(-1.0f, 0.0f)	// left
		};
		float max = 0.0f;
		int closestMatch = -1;
		for (int i = 0; i < 4; i++)
		{
			float dot = glm::dot(glm::normalize(collisionDiff), compass[i]);
			if (dot > max)
			{
				max = dot;
				closestMatch = i;
			}
		}
		return static_cast<Direction>(closestMatch);
	}
}