#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Character.h"
#include "Bullet.h"
#include "Level.h"

class EnemyManager
{
public:
	EnemyManager();

	void init();
	void spawnNewEnemy(std::vector<LevelTile>& m_tiles, std::shared_ptr<sf::Vector2f>& t_player);

	void update();
	void checkHits(std::vector<Bullet>& t_bullets);

private:
	std::vector<std::shared_ptr<Pawn>> m_enemies;
};


#endif // !ENEMY_MANAGER_H
