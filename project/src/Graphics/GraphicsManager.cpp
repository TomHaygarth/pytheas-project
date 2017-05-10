
#include "GraphicsManager.h"

#include "GraphicalStructs.h"
#include "Shader.h"

#include <fstream>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Graphics
{
	GraphicsManager::GraphicsManager(const float & screenWidth, const float & screenHeight, SDL_Window* sdlWindow)
		:m_screenSize(screenWidth, screenHeight)
	{
		m_projectionMatrix = glm::ortho(0.0f, screenWidth, screenHeight, 0.0f, 0.01f, 100.0f);
		//m_projectionMatrix = glm::perspective(60.0f, screenWidth / screenHeight, 0.1f, 100.0f);
		m_viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		m_modelMatrix = glm::mat4(1.0f);

		m_mvpMatrix = m_projectionMatrix * m_viewMatrix * m_modelMatrix;
		//m_mvpMatrix = m_projectionMatrix;
		
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		}
		else
		{
			m_windowSurface = SDL_GetWindowSurface(sdlWindow);
		}
	}

	GraphicsManager::~GraphicsManager()
	{
		std::map<std::string, GLuint>::iterator itTextures = m_textureLookup.begin();
		while (itTextures != m_textureLookup.end())
		{
			glDeleteTextures(1, &(*itTextures).second);
			itTextures = m_textureLookup.erase(itTextures);
		}
	}

	IShader* GraphicsManager::LoadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) const
	{

		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Read the Vertex Shader code from the file
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertexShaderPath, std::ios::in);
		if (VertexShaderStream.is_open())
		{
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}

		// Read the Fragment Shader code from the file
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragmentShaderPath, std::ios::in);
		if (FragmentShaderStream.is_open()) {
			std::string Line = "";
			while (getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}

		GLint Result = GL_FALSE;
		int InfoLogLength;

		// Compile Vertex Shader
		std::cout << "Compiling shader :" << vertexShaderPath << std::endl;
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);

		if (Result == GL_FALSE)
		{
			glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

			char* VertexShaderErrorMessage = new char[InfoLogLength];
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, VertexShaderErrorMessage);
			std::cout << "Error Compiling vertex shader :" << VertexShaderErrorMessage << std::endl;

			delete VertexShaderErrorMessage;
		}

		// Compile Fragment Shader
		std::cout << "Compiling shader :" << fragmentShaderPath << std::endl;
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);

		if (Result == GL_FALSE)
		{
			glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

			char* FragmentShaderErrorMessage = new char[InfoLogLength];
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, FragmentShaderErrorMessage);
			std::cout << "Error Compiling fragment shader :" << FragmentShaderErrorMessage << std::endl;

			delete FragmentShaderErrorMessage;
		}

		// Link the program
		std::cout << "Linking program" << std::endl;
		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		// Check the program
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);

		if (Result == GL_FALSE)
		{
			glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

			char* ProgramErrorMessage = new char[InfoLogLength];
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage);
			std::cout << "Error linking shader program :" << ProgramErrorMessage << std::endl;

			delete ProgramErrorMessage;
		}

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		return new Shader(ProgramID);
	}

	const TEXTURE_INFO GraphicsManager::LoadTexture(const std::string &filename, const GLuint& shaderProgram)
	{
		TEXTURE_INFO texture;

		std::map<std::string, GLuint>::const_iterator itTexture = m_textureLookup.find(filename);

		if (itTexture == m_textureLookup.end())
		{

			SDL_Surface* image = IMG_Load(filename.c_str());
			SDL_PixelFormat pf;
			pf.palette = 0;
			pf.BitsPerPixel = 32;
			pf.BytesPerPixel = 4;
			pf.Rshift = pf.Rloss = pf.Gloss = pf.Bloss = pf.Aloss = 0;
			pf.Rmask = 0x000000ff;
			pf.Gshift = 8;
			pf.Gmask = 0x0000ff00;
			pf.Bshift = 16;
			pf.Bmask = 0x00ff0000;
			pf.Ashift = 24;
			pf.Amask = 0xff000000;

			SDL_Surface* glSurface = SDL_ConvertSurface(image, &pf, SDL_SWSURFACE);

			// create the texture
			glGenTextures(1, &texture.TextureHandle);
			// bind it so we can start modifying the texture 
			glBindTexture(GL_TEXTURE_2D, texture.TextureHandle);
			// pass the image data to the texture
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, glSurface->w, glSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, glSurface->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);

			SDL_FreeSurface(image);
			SDL_FreeSurface(glSurface);

			m_textureLookup[filename] = texture.TextureHandle;
		}
		else
		{
			texture.TextureHandle = (*itTexture).second;
		}
		// get the handle to the texture sampler
		texture.TexSamplerID = glGetUniformLocation(shaderProgram, "myTextureSampler");

		// return the TEXTURE_INFO
		return texture;
	}

	void GraphicsManager::SetViewMatrix(const glm::vec3 &eyePos, const glm::vec3 &centrePoint, const glm::vec3 &up)
	{
		m_viewMatrix = glm::lookAt(eyePos, centrePoint, up);

		m_mvpMatrix = m_projectionMatrix * m_viewMatrix * m_modelMatrix;
	}
}