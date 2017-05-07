
#pragma once

#include <glm/glm.hpp>

namespace Graphics
{
	namespace Sprites
	{
		class ISprite
		{
		public:
			virtual const glm::vec3& GetPosition() const = 0;
			virtual const glm::vec2& GetSize() const = 0;
			virtual const glm::vec3& GetColor() const = 0;
			virtual void SetPosition(const glm::vec3& position) = 0;
			virtual void SetRotation(const float& rotation) = 0;
			virtual void SetColor(const glm::vec3& color) = 0;
			virtual void Render() const = 0;
		};
	}
}