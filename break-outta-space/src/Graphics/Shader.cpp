
#include "Shader.h"

namespace Graphics
{
	Shader::Shader(const GLuint& shaderID) 
		: mShaderID(shaderID)
	{
	}
	Shader::~Shader()
	{
		glDeleteProgram(mShaderID);
	}

	void Shader::AddBuffer(GLuint bufferID, GLuint index, GLuint elementSize, GLenum type, GLboolean normalised, GLsizei stride, GLvoid *pointer)
	{
		BUFFER_INFO buffer = { bufferID, index, elementSize, type, normalised, stride, pointer };
		m_buffers.push_back(buffer);
	}

	void Shader::SetMatrixAttrib(const std::string& name, glm::mat4 &matrix)
	{
		SetAttrib(name, matrix[0][0], MATRIX4);
	}

	void Shader::SetVec4Attrib(const std::string& name, glm::vec4 &vec4)
	{
		SetAttrib(name, vec4[0], VEC4);
	}

	void Shader::SetVec3Attrib(const std::string& name, glm::vec3 &vec3)
	{
		SetAttrib(name, vec3[0], VEC3);
	}

	void Shader::SetVec2Attrib(const std::string& name, glm::vec2 &vec2)
	{
		SetAttrib(name, vec2[0], VEC2);
	}

	void Shader::SetFloatAttrib(const std::string& name, float &value)
	{
		SetAttrib(name, value, FLOAT);
	}

	void Shader::Activate() const
	{
		// activate our shader
		glUseProgram(mShaderID);

		// loop through all the buffers
		for (int i = m_buffers.size() - 1; i >= 0; --i)
		{
			// enable the vertex attribute
			glEnableVertexAttribArray(i);

			// bind the buffer
			glBindBuffer(GL_ARRAY_BUFFER, m_buffers[i].bufferID);

			// set the atribute pointer to the buffer for our vertex shader
			glVertexAttribPointer(m_buffers[i].index, m_buffers[i].elementSize, m_buffers[i].type, m_buffers[i].normalised, m_buffers[i].stride, m_buffers[i].pointer);
		}

		// loop through all uniform attributes
		for (std::map<std::string, ATTRIB_INFO>::const_iterator it = m_attributes.begin(); it != m_attributes.end(); it++)
		{
			switch (it->second.mType)
			{
			case MATRIX4:
				glUniformMatrix4fv(it->second.mLocationID, 1, GL_FALSE, it->second.mData);
				break;

			case VEC4:
				glUniform4fv(it->second.mLocationID, 1, it->second.mData);
				break;

			case VEC3:
				glUniform3fv(it->second.mLocationID, 1, it->second.mData);
				break;

			case VEC2:
				glUniform2fv(it->second.mLocationID, 1, it->second.mData);
				break;

			case FLOAT:
				glUniform1fv(it->second.mLocationID, 1, it->second.mData);
				break;

			}
		}

	}

	void Shader::Deactivate() const
	{
		// loop through all the buffers
		for (int i = m_buffers.size() - 1; i >= 0; --i)
		{
			// disable the vertex attribute
			glDisableVertexAttribArray(m_buffers[i].index);

		}
	}
	void Shader::SetAttrib(const std::string & name, float & value, const Attrib_Type & type)
	{
		ATTRIB_INFO attribute;
		attribute.mLocationID = glGetUniformLocation(mShaderID, name.c_str());
		attribute.mType = type;
		attribute.mData = &value;
		m_attributes[name] = attribute;
	}
}