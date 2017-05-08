
#pragma once

#include "GameObject.h"

namespace GameComponents
{
	class Paddle : public GameObject
	{
	public:
		Paddle(Graphics::Sprites::ISprite* sprite, const glm::vec3& position, const float& minXBound = 0.0f, const float& maxXBound = 1280.0f);

		void MoveLeft(const float& deltatime);
		void MoveRight(const float& deltatime);

	private:
		float m_minXBound;
		float m_maxXBound;
	};
}