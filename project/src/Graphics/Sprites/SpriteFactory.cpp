
#include "SpriteFactory.h"

#include "../IShader.h"
#include "Sprite.h"
#include <algorithm>

namespace Graphics
{
	namespace Sprites
	{
		SpriteFactory::SpriteFactory()
		{
			glm::vec3 vertices[6] =
			{
				glm::vec3(-0.5f, 0.5f, 0.0f), //top-left
				glm::vec3(-0.5f, -0.5f, 0.0f), //bot-left
				glm::vec3(0.5f, 0.5f, 0.0f), //top-right
				glm::vec3(0.5f, -0.5f, 0.0f)  //bot-right
			};
			glm::vec2 uvs[4] =
			{
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 0.0f)
			};

			GLuint indecies[6] =
			{
				0, 1, 2,
				2, 1, 3
			};

			glGenBuffers(1, &m_vertexBuff);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuff);
			glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

			glGenBuffers(1, &m_uvBuff);
			glBindBuffer(GL_ARRAY_BUFFER, m_uvBuff);
			glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

			glGenBuffers(1, &m_indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), &indecies[0], GL_STATIC_DRAW);
		}

		SpriteFactory::~SpriteFactory()
		{
			glDeleteBuffers(1, &m_indexBuffer);
			glDeleteBuffers(1, &m_uvBuff);
			glDeleteBuffers(1, &m_vertexBuff);
		}

		ISprite * SpriteFactory::CreateSprite(TEXTURE_INFO & texture, IShader & shader, const glm::vec2 size, 
			const glm::vec3 & position, const float & rotation, const glm::vec3& color)
		{
			std::vector<GLuint>::const_iterator it = std::find(m_usedShaders.begin(), m_usedShaders.end(), shader.GetShaderID());
			if(it == m_usedShaders.end())
			{
				shader.AddBuffer(m_vertexBuff, 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
				shader.AddBuffer(m_uvBuff, 1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
				m_usedShaders.push_back(shader.GetShaderID());
			}

			return new Sprite(texture, shader, m_indexBuffer, size, position, rotation, color);
		}
	}
}