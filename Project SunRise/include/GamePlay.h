#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "GameMode.h"
#include "Player.h"
#include "TileLookupTable.h"

// for debugging purposes
#include "SimpleButton.h"
#include "LevelLoader.h"
#include "BulletManager.h"

class GamePlay : public GameMode
{
public:
	GamePlay();  // standard constructor
	~GamePlay(); // standard deconstructor (shouldnt be used)

	void resetLevel()override;                         // used to reset the level for each session instead of reconstructing
	void events(sf::Event& t_event)override;           // used to handle all new events outside key presses
	void update()override;         // all update events

private:
	void processKeys(sf::Event& t_event)override;      // handles all key inputs
	void processMouse(sf::Event& t_event)override;     // handles all mouse events

	void spawnTiles();

	Player m_player;
	std::vector<std::shared_ptr<sf::Sprite>> m_tiles;

	BulletManager m_bulletManager;
};

#endif // !GAMEPLAY_H
