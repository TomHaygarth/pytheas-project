
#include "BlockManager.h"
#include "Block.h"
#include "Ball.h"
#include "Blackhole.h"
#include "../Graphics/Sprites/ISpriteFactory.h"
#include "../Physics2D/IAABBCollider2D.h"
#include <sstream>
#include <fstream>
#include <stdlib.h>

namespace GameComponents
{
	BlockManager::BlockManager(Graphics::Sprites::ISpriteFactory& spriteFactory, const Graphics::TEXTURE_INFO & blockTexture, Graphics::TEXTURE_INFO const & blackholeTexture, Graphics::IShader & shader)
		:m_spriteFactory(spriteFactory),
        m_blockTexture(blockTexture),
        m_blackholeTexture(blackholeTexture),
		m_shader(shader),
		m_maxBlockColumns(10),
		m_maxBlockRows(8)
	{
	}

	BlockManager::~BlockManager()
	{
		CleanupBlocks();
        CleanupBlackholes();
	}

	bool BlockManager::LoadLevel(const int & level)
	{
		CleanupBlocks();
        CleanupBlackholes();

		std::ostringstream filePath;
		filePath << "Resources/Levels/level_" << level << ".txt";

		std::ifstream levelFile;

		levelFile.open(filePath.str());
		
		if (!levelFile.is_open())
		{
			return false;
		}

		std::string strBuff;

		int j = 0;

		while (!levelFile.eof() && j < m_maxBlockRows)
		{
			std::getline(levelFile, strBuff);

			for (int i = 0; i < m_maxBlockColumns; ++i)
			{
				if (i >= static_cast<int>(strBuff.length()))
				{
					break;
				}

				switch (strBuff[i])
				{
				case '1':
					CreateBlock(i, j, 1, glm::vec3(0.1f,1.0f,0.1f));
					break;
				case '2':
					CreateBlock(i, j, 2, glm::vec3(1.0f, 0.5f, 0.1f));
					break;
                case 'b':
                    CreateBlackhole(i, j, 1.0f, 50.0f);
                    break;
                case 'B':
                    CreateBlackhole(i, j, 2.0f, 125.0f);
                    break;
				default:
					break;
				}
			}
			++j;
		}

		levelFile.close();

		m_blocksRemaining = static_cast<int>(m_blocks.size());

		return true;
	}

	void BlockManager::CheckBlockCollisions(Ball & ball)
	{
		std::list<Block*>::const_iterator itBlocks = m_blocks.begin();
		while(itBlocks != m_blocks.end())
		{
			BallCollision collision = ball.CheckCollision(*(*itBlocks));
			if(std::get<0>(collision))
			{
				glm::vec2 collisionDiff = std::get<1>(collision);
				ball.ReactToCollision(collisionDiff);

				if ((*itBlocks)->Strength() == 2)
				{
					float r = static_cast<float>(rand()) / static_cast<float>((RAND_MAX));
					float g = static_cast<float>(rand()) / static_cast<float>((RAND_MAX));
					float b = static_cast<float>(rand()) / static_cast<float>((RAND_MAX));
					ball.SetColor(glm::vec3(r,g,b));
				}

				(*itBlocks)->Damage();

				if ((*itBlocks)->Destroyed())
				{
					delete (*itBlocks);
					itBlocks = m_blocks.erase(itBlocks);
					continue;
				}
			}
			++itBlocks;
		}

		m_blocksRemaining = static_cast<int>(m_blocks.size());
	}
	void BlockManager::RenderBlocks() const
	{
		
		for(std::list<Block*>::const_iterator itBlocks = m_blocks.begin(); itBlocks != m_blocks.end(); ++itBlocks)
		{
			(*itBlocks)->Render();
		}

        for (std::vector<Blackhole *>::const_iterator itBlackholes = m_blackholes.begin(); itBlackholes != m_blackholes.end(); ++itBlackholes)
        {
            (*itBlackholes)->Render();
        }
	}

    const float blockWidth = 128.0f;
    const float blockHeight = 64.0f;

	void BlockManager::CreateBlock(int gridColumn, int gridRow, int strength, glm::vec3 color)
	{

		glm::vec3 position((static_cast<float>(gridColumn) * blockWidth) + (blockWidth * 0.5f), (static_cast<float>(gridRow) * blockHeight) + (blockHeight * 0.5f), 0.0f);
		Graphics::Sprites::ISprite* blockSprite = m_spriteFactory.CreateSprite(m_blockTexture, m_shader, glm::vec2(blockWidth, blockHeight), position, 0.0f, color);

		Block* block = new Block(blockSprite, position, strength);

		m_blocks.push_back(block);
	}
	void BlockManager::CleanupBlocks()
	{
		std::list<Block*>::iterator itBlocks = m_blocks.begin();
		while (itBlocks != m_blocks.end())
		{
			delete (*itBlocks);
			itBlocks = m_blocks.erase(itBlocks);
		}
	}

    void BlockManager::CreateBlackhole(int gridColumn, int gridRow, float const size, float const gravitationalDensity)
    {
        float constexpr blackholeDefaultDiameter = 32.0f;
        float constexpr blackholeDefaultCollisionRadius = 12.0f;
        float const blackholeDiameter = blackholeDefaultDiameter * size;
        float const blackholeCollisionRadius = blackholeDefaultCollisionRadius * size;

        glm::vec3 position((static_cast<float>(gridColumn) * blockWidth) + (blockWidth * 0.5f), (static_cast<float>(gridRow) * blockHeight) + (blockHeight * 0.5f), 0.0f);

        Graphics::Sprites::ISprite* blackholeSprite = m_spriteFactory.CreateSprite(m_blackholeTexture, m_shader, glm::vec2(blackholeDiameter, blackholeDiameter), position, 0.0f, glm::vec3(1.0f));

        Blackhole* blackhole = new Blackhole(blackholeSprite, position, blackholeCollisionRadius, gravitationalDensity);

        m_blackholes.push_back(blackhole);
    }
    void BlockManager::CleanupBlackholes()
    {
        std::vector<Blackhole*>::iterator itBlackhole = m_blackholes.begin();
        while (itBlackhole != m_blackholes.end())
        {
            delete (*itBlackhole);
            itBlackhole = m_blackholes.erase(itBlackhole);
        }
    }
}