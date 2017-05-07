
#pragma once

#include "Graphics.h"
#include "IGraphicsManager.h"

#include <SDL.h>
#include <map>
#include <string>

namespace Graphics
{
	class GraphicsManager : public IGraphicsManager
	{
	public:

		GraphicsManager(const float& screenWidth, const float& screenHeight, SDL_Window* sdlWindow);
		~GraphicsManager();

		IShader* LoadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) const;
		const TEXTURE_INFO LoadTexture(const std::string &filename, const GLuint& shaderProgram);
		void SetViewMatrix(const glm::vec3 &eyePos, const glm::vec3 &centrePoint, const glm::vec3 &up);

		const glm::mat4& GetMVPMatrix() const { return m_mvpMatrix; }
		const glm::vec2& GetScreenSize() const { return m_screenSize; }

	private:

		glm::vec2 m_screenSize;

		bool m_useOrthographic;

		glm::mat4 m_modelMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_mvpMatrix;

		SDL_Surface* m_windowSurface;
		std::map<std::string, GLuint> m_textureLookup;
	};
}