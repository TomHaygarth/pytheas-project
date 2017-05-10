
#pragma once

#include "../Graphics.h"
#include "ISpriteFactory.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <GL/glew.h>

namespace Graphics
{
	namespace Sprites
	{
		class SpriteFactory : public ISpriteFactory
		{
		public:

			SpriteFactory();
			~SpriteFactory();

			ISprite* CreateSprite(TEXTURE_INFO& texture, IShader& shader, const glm::vec2 size, 
				const glm::vec3& position = glm::vec3(0, 0, 0), const float& rotation = 0.0f, const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f));

		private:

			std::vector<GLuint> m_usedShaders;

			GLuint m_vertexBuff;
			GLuint m_indexBuffer;
			GLuint m_uvBuff;
		};
	}
}