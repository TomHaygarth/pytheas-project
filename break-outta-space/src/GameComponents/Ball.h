
#pragma once
#include "GameComponents.h"
#include "GameObject.h"
#include "../Graphics/Sprites/ISprite.h"
#include <glm/vec2.hpp>
#include <tuple>

namespace GameComponents
{
	typedef std::tuple<bool, glm::vec2> BallCollision;

	class Ball : public GameObject
	{
	public:

		Ball(Graphics::Sprites::ISprite * sprite, const glm::vec3& position, const float& collisionRadius,
			const glm::vec2& minBounds = glm::vec2(0.0f,0.0f), const glm::vec2& maxBounds = glm::vec2(1280.0f, 720.0f));

		void Respawn();
		void UpdateMovement(const float& deltaTimeS, const Paddle& paddle);
		BallCollision CheckCollision(const GameObject& objectCentre) const;
		void ReactToCollision(const glm::vec2& collisionDiff);
		void ReactToPaddle(const Paddle& paddle);
		void LaunchBall() { m_isStuck = false; }
		void SetColor(const glm::vec3& color) { m_sprite->SetColor(color); }

		const bool HasLaunched() const { return !m_isStuck; }

	private:

		enum Direction{
			UP,
			RIGHT,
			DOWN,
			LEFT
		};

		Direction CollisionDirection(const glm::vec2& collisionDiff);

		glm::vec2 m_minBounds;
		glm::vec2 m_maxBounds;
		glm::vec2 m_velocity;
		bool m_isStuck;
		const glm::vec2 m_initialBallVelocity;
		float m_collisionRadius;
	};
}