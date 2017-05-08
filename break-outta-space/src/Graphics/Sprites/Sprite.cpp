
#include "Sprite.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../IShader.h"
#include "../GraphicalStructs.h"

namespace Graphics
{
	namespace Sprites
	{
		Sprite::Sprite(const TEXTURE_INFO & texture, IShader & shader, GLuint& indexBuff, const glm::vec2& size,
			const glm::vec3 & position, const float & rotation, const glm::vec3& color)
			:m_texture(texture),
			m_shader(shader),
			m_indexBuffer(indexBuff),
			m_size(size),
			m_position(position),
			m_rotation(rotation),
			m_color(color),
			m_indexCount(6)
		{
			
		}

		Sprite::~Sprite()
		{
		}

		void Sprite::Render() const
		{
			glm::mat4 modelMat(1.0f);
			modelMat = glm::translate(modelMat, m_position);
			modelMat = glm::rotate(modelMat, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
			modelMat = glm::scale(modelMat, glm::vec3(m_size, 1.0f));
			m_shader.SetMatrixAttrib("ModelTransform", modelMat);
			m_shader.SetVec3Attrib("SpriteColor", glm::vec3(m_color));

			glUniform1i(m_texture.TexSamplerID, 0);

			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_texture.TextureHandle);

			m_shader.Activate();

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, (void*)0);

			m_shader.Deactivate();
		}
	}
}