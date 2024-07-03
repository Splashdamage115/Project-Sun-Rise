#ifndef LEVEL_H
#define LEVEL_H

#include "Library.h"

struct LevelTile
{
	std::shared_ptr<sf::Sprite> m_tile;

};

struct	LevelCluster 
{
	bool m_active = false;
	std::vector<LevelTile> m_tilesSprite;
	std::vector<std::shared_ptr<sf::Sprite>> m_bridgeTiles;
};

class Level
{
public:
	Level();

	void generateNewLevel();
	
	std::vector<LevelTile>& getTiles(sf::Vector2f t_activeCluster);
	std::vector<std::shared_ptr<sf::Sprite>>& getColliders() { return m_collidingBox; }
	void generateBridges(float t_xOff, float t_yOff, std::vector<float>& t_heights, int t_pos);
	void generateWalls(float t_xOff, float t_yOff, std::vector<float>& t_heights);
private:
	void generateTileCluster(float t_xOff, float t_yOff, std::vector<int>& t_level, std::vector<float>& t_heights);
	void sortTiles(std::vector<float> t_heights);

	std::vector<LevelCluster> m_tiles;
	std::vector<std::shared_ptr<sf::Sprite>> m_collidingBox;
};

#endif // !LEVEL_H
