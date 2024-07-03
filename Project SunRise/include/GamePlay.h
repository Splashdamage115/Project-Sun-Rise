#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "GameMode.h"
#include "Character.h"
#include "TileLookupTable.h"
#include "Level.h"

// for debugging purposes
#include "SimpleButton.h"
#include "LevelLoader.h"
#include "BulletManager.h"
#include "EnemyManager.h"

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

	Character m_player;

	BulletManager m_bulletManager;
	EnemyManager m_enemyManager;
	Level m_levelHolder;
};

#endif // !GAMEPLAY_H
