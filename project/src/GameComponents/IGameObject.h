
#pragma once

#include <glm/vec3.hpp>
#include "../Physics2D/Physics2D.h"

namespace GameComponents
{
	class IGameObject
	{
	public:
		virtual void SetPosition(const glm::vec3& position) = 0;
		virtual const glm::vec3& GetPosition() const = 0;
		virtual const glm::vec2& GetSize() const = 0;
		virtual const Physics2D::IAABBCollider2D& GetAABBColider() const = 0;
		virtual void Render() const = 0;
	};
}

