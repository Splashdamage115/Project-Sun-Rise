#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Character.h"
#include "Bullet.h"

class EnemyManager
{
public:
	EnemyManager();

	void init();
	void spawnNewEnemy(int t_spawnCluster, std::vector<std::shared_ptr<sf::Sprite>>& m_tiles);

	void update();
	void checkHits(std::vector<Bullet>& t_bullets);

private:
	std::vector<std::shared_ptr<Pawn>> m_enemies;
};


#endif // !ENEMY_MANAGER_H
