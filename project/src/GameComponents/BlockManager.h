
#pragma once
#include "GameComponents.h"
#include "IBlockManager.h"

#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicalStructs.h"

#include <list>
#include <vector>
#include <glm/vec3.hpp>

namespace GameComponents
{
	class BlockManager : public IBlockManager
	{
	public:

        BlockManager(Graphics::Sprites::ISpriteFactory& spriteFactory, Graphics::TEXTURE_INFO const & blockTexture, Graphics::TEXTURE_INFO const & blackholeTexture, Graphics::IShader & shader);
		~BlockManager();

		bool LoadLevel(const int& level);
		void CheckBlockCollisions(Ball& ball);
		void RenderBlocks() const;
		const int& BlocksLeft() const { return m_blocksRemaining; }

        std::vector<Blackhole *> const & GetBlackholes() const { return m_blackholes; }

	private:

		void CreateBlock(int gridColumn, int gridRow, int strength, glm::vec3 color);
		void CleanupBlocks();

        void CreateBlackhole(int gridColumn, int gridRow, float const size, float const gravitationalDensity);
        void CleanupBlackholes();

		Graphics::Sprites::ISpriteFactory& m_spriteFactory;
		int m_blocksRemaining;

		const int m_maxBlockColumns;
		const int m_maxBlockRows;

        Graphics::TEXTURE_INFO m_blockTexture;
        Graphics::TEXTURE_INFO m_blackholeTexture;
		Graphics::IShader & m_shader;

		std::list<Block*> m_blocks;
        std::vector<Blackhole *> m_blackholes;
	};
}