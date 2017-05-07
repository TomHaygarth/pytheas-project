
#pragma once

#include "Graphics.h"

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Graphics
{
	class IGraphicsManager
	{
	public:
		virtual IShader* LoadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) const = 0;
		virtual const TEXTURE_INFO LoadTexture(const std::string &filename, const GLuint& shaderProgram) = 0;
		virtual void SetViewMatrix(const glm::vec3 &eyePos, const glm::vec3 &centrePoint, const glm::vec3 &up) = 0;
		virtual const glm::mat4& GetMVPMatrix() const = 0;
		virtual const glm::vec2& GetScreenSize() const = 0;
	};
}