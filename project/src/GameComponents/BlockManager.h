
#pragma once
#include "GameComponents.h"
#include "IBlockManager.h"

#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicalStructs.h"

#include <list>
#include <glm/vec3.hpp>

namespace GameComponents
{
	class BlockManager : public IBlockManager
	{
	public:

		BlockManager(Graphics::Sprites::ISpriteFactory& spriteFactory, const Graphics::TEXTURE_INFO & texture, Graphics::IShader & shader);
		~BlockManager();

		bool LoadLevel(const int& level);
		void CheckBlockCollisions(Ball& ball);
		void RenderBlocks() const;
		const int& BlocksLeft() const { return m_blocksRemaining; }

	private:

		void CreateBlock(int gridColumn, int gridRow, int strength, glm::vec3 color);
		void CleanupBlocks();

		Graphics::Sprites::ISpriteFactory& m_spriteFactory;
		int m_blocksRemaining;

		const int m_maxBlockColumns;
		const int m_maxBlockRows;

		Graphics::TEXTURE_INFO m_texture;
		Graphics::IShader & m_shader;

		std::list<Block*> m_blocks;
	};
}