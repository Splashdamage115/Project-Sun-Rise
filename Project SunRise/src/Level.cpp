#include "Level.h"
#include "TileLookupTable.h"
#include "LevelLoader.h"
#include "RenderObject.h"
#include "simpleMaths.h"
#include "TextureLoader.h"

Level::Level()
{
}

void Level::generateNewLevel()
{
	LevelLoader levelLoader;
	std::vector<int>level = levelLoader.readFileToBuffer(rand() % MAP_AMT + 1);


	RenderObject::getInstance().clearBG();
	m_tiles.clear();

	
	std::vector<float> heights;


	int xBackBig = -1;
	int heightBig = 4; // height of tiles on the diagonal (how many level tiles will spawn)
	float widthBig = 2048.f; // change this to change distance between tile sets
	float xOffset = 0.f;
	float yOffset = 0.f;

	// 16 is the amount of level tiles spawned
	for (unsigned int u = 0; u < 16; u++)
	{
		if (u % heightBig == 0)
			xBackBig++;

		xOffset = -((xBackBig) * (widthBig)) + ((u % heightBig) * (widthBig));
		yOffset = (u % heightBig) * (widthBig / 2.f) + (xBackBig * (widthBig / 2.f));

		level = levelLoader.readFileToBuffer(rand() % 7 + 1);

		generateTileCluster(xOffset, yOffset, level, heights);

		generateBridges(xOffset, yOffset, heights, u);
		
		generateWalls(xOffset, yOffset, heights);
	}
	sortTiles(heights);
}

std::vector<LevelTile>& Level::getTiles(sf::Vector2f t_activeCluster)
{ 
	for (auto& i : m_tiles)
	{
		float tileSetRadius = 986.f;

		if(math::positionInCircle(i.m_tilesSprite.at(0).m_tile->getPosition() + sf::Vector2f(0.f, tileSetRadius / 2.f), tileSetRadius, t_activeCluster))
			return i.m_tilesSprite;
	}
	return m_tiles.at(1).m_tilesSprite;
}

void Level::generateBridges(float t_xOff, float t_yOff, std::vector<float>& t_heights, int t_pos)
{
	float scaleFactor = 1.f;
	int height = 16;
	float width = 62.f;
	for (int i = 0; i < 17; i++)
	{
		std::shared_ptr<sf::Sprite> newTile;
		if(t_pos != 3 && t_pos != 7 && t_pos != 11 && t_pos != 15)
		{
			newTile = std::make_shared<sf::Sprite>();
			newTile->setTexture(TileLookupTable::getInstance().getNumber(4).tileTexture);
			newTile->setOrigin(newTile->getGlobalBounds().width / 2.f, newTile->getGlobalBounds().height / 2.f);
			newTile->setScale(scaleFactor, scaleFactor);
			newTile->setPosition(t_xOff - ((-8 - i) * (width * scaleFactor)) + ((0 % height) * (width * scaleFactor)), t_yOff + (0 % height) * (width / 2.f * scaleFactor) + ((24 + i) * (width / 2.f * scaleFactor)));

			m_tiles.at(t_pos).m_bridgeTiles.push_back(newTile);

			newTile = std::make_shared<sf::Sprite>();
			newTile->setTexture(TileLookupTable::getInstance().getNumber(4).tileTexture);
			newTile->setOrigin(newTile->getGlobalBounds().width / 2.f, newTile->getGlobalBounds().height / 2.f);
			newTile->setScale(scaleFactor, scaleFactor);
			newTile->setPosition(t_xOff - ((-9 - i) * (width * scaleFactor)) + ((0 % height) * (width * scaleFactor)), t_yOff + (0 % height) * (width / 2.f * scaleFactor) + ((23 + i) * (width / 2.f * scaleFactor)));
			m_tiles.at(t_pos).m_bridgeTiles.push_back(newTile);

		}

		if (t_pos != 12 && t_pos != 13 && t_pos != 14 && t_pos != 15)
		{
			newTile = std::make_shared<sf::Sprite>();
			newTile->setTexture(TileLookupTable::getInstance().getNumber(6).tileTexture);
			newTile->setOrigin(newTile->getGlobalBounds().width / 2.f, newTile->getGlobalBounds().height / 2.f);
			newTile->setScale(scaleFactor, scaleFactor);
			newTile->setPosition(t_xOff - ((9 + i) * (width * scaleFactor)) + ((0 % height) * (width * scaleFactor)), t_yOff + (0 % height) * (width / 2.f * scaleFactor) + ((23 + i) * (width / 2.f * scaleFactor)));

			m_tiles.at(t_pos).m_bridgeTiles.push_back(newTile);

			newTile = std::make_shared<sf::Sprite>();
			newTile->setTexture(TileLookupTable::getInstance().getNumber(6).tileTexture);
			newTile->setOrigin(newTile->getGlobalBounds().width / 2.f, newTile->getGlobalBounds().height / 2.f);
			newTile->setScale(scaleFactor, scaleFactor);
			newTile->setPosition(t_xOff - ((8 + i) * (width * scaleFactor)) + ((0 % height) * (width * scaleFactor)), t_yOff + (0 % height) * (width / 2.f * scaleFactor) + ((24 + i) * (width / 2.f * scaleFactor)));
			m_tiles.at(t_pos).m_bridgeTiles.push_back(newTile);
		}
	}
}

void Level::generateWalls(float t_xOff, float t_yOff, std::vector<float>& t_heights)
{
	int xBack = -1;
	float scaleFactor = 1.f;
	int height = 16;
	float width = 62.f;

	for (unsigned int i = 0; i < 256; i++)
	{
		if (i % height == 0)
			xBack++;

		bool south = (i % height == 15);
		bool north = (i % height == 0);

		if (!(north) && !(south))
		{
			continue;
		}

		std::shared_ptr<sf::Sprite> newBox;
		newBox = std::make_shared<sf::Sprite>();
		if(north)
		newBox->setTexture(*TextureLoader::getInstance().getTexture(".\\ASSETS\\IMAGES\\Tile\\WallLeft.png"));
		if(south)
			newBox->setTexture(*TextureLoader::getInstance().getTexture(".\\ASSETS\\IMAGES\\Tile\\WallRightBottom.png"));

		newBox->setPosition(t_xOff - ((xBack) * (width * scaleFactor)) + ((i % height) * (width * scaleFactor)), t_yOff + (i % height) * (width / 2.f * scaleFactor) + (xBack * (width / 2.f * scaleFactor)));
		newBox->setOrigin(newBox->getGlobalBounds().width / 2.f, newBox->getGlobalBounds().height / 2.f);


		m_collidingBox.push_back(newBox);
	}

	xBack = 0;

	for (unsigned int i = 0; i < 16; i++)
	{
		std::shared_ptr<sf::Sprite> newBox;
		newBox = std::make_shared<sf::Sprite>();
		newBox->setTexture(*TextureLoader::getInstance().getTexture(".\\ASSETS\\IMAGES\\Tile\\WallRight.png"));
		newBox->setPosition(t_xOff - ((xBack) * (width * scaleFactor)) + ((i % height) * (width * scaleFactor)), t_yOff + (i % height) * (width / 2.f * scaleFactor) + (xBack * (width / 2.f * scaleFactor)));
		newBox->setOrigin(newBox->getGlobalBounds().width / 2.f, newBox->getGlobalBounds().height / 2.f);


		m_collidingBox.push_back(newBox);
	}
}

void Level::generateTileCluster(float t_xOff, float t_yOff, std::vector<int>& t_level, std::vector<float>& t_heights)
{
	LevelCluster tiles;
	int xBack = -1;
	float scaleFactor = 1.f;
	int height = 16;
	float width = 62.f;
	for (unsigned int i = 0; i < 256; i++)
	{
		if (i % height == 0)
			xBack++;
		LevelTile newTile;
		newTile.m_tile = std::make_shared<sf::Sprite>();
		newTile.m_tile->setTexture(TileLookupTable::getInstance().getNumber(t_level.at(i)).tileTexture);
		newTile.m_tile->setOrigin(newTile.m_tile->getGlobalBounds().width / 2.f, newTile.m_tile->getGlobalBounds().height / 2.f);
		newTile.m_tile->setScale(scaleFactor, scaleFactor);
		newTile.m_tile->setPosition(t_xOff - ((xBack) * (width * scaleFactor)) + ((i % height) * (width * scaleFactor)), t_yOff + (i % height) * (width / 2.f * scaleFactor) + (xBack * (width / 2.f * scaleFactor)));
		bool addNew = true;
		for (unsigned int u = 0; u < t_heights.size(); u++)
		{
			if (newTile.m_tile->getPosition().y == t_heights.at(u))
			{
				addNew = false;
				break;
			}
		}
		if (addNew)
			t_heights.push_back(newTile.m_tile->getPosition().y);
		tiles.m_tilesSprite.push_back(newTile);
	}
	

	m_tiles.push_back(tiles);


}

void Level::sortTiles(std::vector<float> t_heights)
{
	std::sort(t_heights.begin(), t_heights.end());

	
	for (auto& tile : m_tiles)
	{
		for (unsigned int u = 0; u < t_heights.size(); u++)
		{
			for (unsigned int i = 0; i < tile.m_tilesSprite.size(); i++)
			{
				if (tile.m_tilesSprite.at(i).m_tile->getPosition().y == t_heights.at(u))
				{
					RenderObject::getInstance().addBG(tile.m_tilesSprite.at(i).m_tile);
				}
			}
		}

		for (unsigned int i = 0; i < tile.m_bridgeTiles.size(); i++)
		{
			RenderObject::getInstance().addBG(tile.m_bridgeTiles.at(i));
		}
	}
	for (unsigned int i = 0; i < m_collidingBox.size(); i++)
	{
		RenderObject::getInstance().addBG(m_collidingBox.at(i));
	}
	
}
