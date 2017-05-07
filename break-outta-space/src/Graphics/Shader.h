
#pragma once

#include "IShader.h"
#include <vector>
#include <map>

namespace Graphics
{
	class Shader : public IShader
	{
	public:

		Shader(const GLuint& shaderID);
		~Shader();

		const GLuint& GetShaderID() const { return mShaderID; }

		void AddBuffer(GLuint bufferID, GLuint index, GLuint elementSize, GLenum type, GLboolean normalised = GL_FALSE, GLsizei stride = 0, GLvoid *pointer = (void*)0);

		void SetMatrixAttrib(const std::string& name, glm::mat4 &matrix);
		void SetVec4Attrib  (const std::string& name, glm::vec4 &vec4);
		void SetVec3Attrib  (const std::string& name, glm::vec3 &vec3);
		void SetVec2Attrib  (const std::string& name, glm::vec2 &vec2);
		void SetFloatAttrib (const std::string& name, float &value);

		void Activate() const;
		void Deactivate() const;

#pragma region Internal_Data_Structs
	private:

		/// <summary>
		struct BUFFER_INFO
		{
			GLuint bufferID;
			GLuint index;
			GLuint elementSize;
			GLenum type;
			GLboolean normalised;
			GLsizei stride;
			GLvoid *pointer;
		};

		enum Attrib_Type
		{
			MATRIX4,
			VEC4,
			VEC3,
			VEC2,
			FLOAT
		};

		struct ATTRIB_INFO
		{
			GLuint mLocationID;
			Attrib_Type mType;
			GLfloat * mData;
		};

#pragma endregion

	private:

		void SetAttrib(const std::string& name, float &value, const Attrib_Type& type);

		GLuint mShaderID;
		std::vector<BUFFER_INFO> m_buffers;

		std::map<std::string, ATTRIB_INFO> m_attributes;
	};
}