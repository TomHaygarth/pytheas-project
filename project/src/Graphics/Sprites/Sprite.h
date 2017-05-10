
#pragma once

#include "../Graphics.h"
#include "ISprite.h"
#include <GL/glew.h>
#include <glm/detail/type_mat.hpp>
#include "../GraphicalStructs.h"

namespace Graphics
{
	namespace Sprites
	{
		class Sprite : public ISprite
		{
		public:
			Sprite(const TEXTURE_INFO& texture, IShader& shader, GLuint& indexBuff, const glm::vec2& size, 
				const glm::vec3& position = glm::vec3(0, 0, 0), const float& rotation = 0.0f, const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f));
			~Sprite();

			const glm::vec3& GetPosition() const { return m_position; }
			const glm::vec2& GetSize() const { return m_size; }
			const glm::vec3& GetColor() const { return m_color; }

			void SetPosition(const glm::vec3& position) { m_position = position; }
			void SetRotation(const float& rotation) { m_rotation = rotation; }
			void SetColor(const glm::vec3& color) { m_color = color; }
			void Render() const;

		private:

			float m_rotation;
			glm::vec3 m_position;
			glm::vec2 m_size;
			glm::vec3 m_color;
			IShader& m_shader;
			TEXTURE_INFO m_texture;

			GLuint m_indexBuffer;

			const int m_indexCount;
		};
	}
}