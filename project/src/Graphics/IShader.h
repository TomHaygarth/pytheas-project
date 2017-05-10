
#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>

namespace Graphics
{
	class IShader
	{
	public:
		virtual const GLuint& GetShaderID() const = 0;
		virtual void AddBuffer(GLuint bufferID, GLuint index, GLuint elementSize, GLenum type, GLboolean normalised = GL_FALSE, GLsizei stride = 0, GLvoid *pointer = (void*)0) = 0;
		virtual void SetMatrixAttrib(const std::string& name, glm::mat4 &matrix) = 0;
		virtual void SetVec4Attrib(const std::string& name, glm::vec4 &vec4) = 0;
		virtual void SetVec3Attrib(const std::string& name, glm::vec3 &vec3) = 0;
		virtual void SetVec2Attrib(const std::string& name, glm::vec2 &vec2) = 0;
		virtual void SetFloatAttrib(const std::string& name, float &value) = 0;
		virtual void Activate() const = 0;
		virtual void Deactivate() const = 0;
	};
}