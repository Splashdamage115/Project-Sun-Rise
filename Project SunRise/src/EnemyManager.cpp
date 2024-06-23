#include "EnemyManager.h"
#include "TextureLoader.h"
#include "CollisionDetector.h"

EnemyManager::EnemyManager()
{
}

void EnemyManager::init()
{
}


void EnemyManager::spawnNewEnemy(int t_spawnCluster, std::vector<std::shared_ptr<sf::Sprite>>& m_tiles)
{
	std::shared_ptr<Pawn> newEnemy;

	newEnemy = std::make_shared<Character>();
	newPawnInfo TargetInfo;
	TargetInfo.level = 1;
	TargetInfo.lockCamera = false;
	TargetInfo.movementType = InputType::None;
	TargetInfo.moveSpeed = 0.f;



	int position = rand() % 256;

	int picked = position + (t_spawnCluster * 256);

	sf::Vector2f pos = m_tiles.at(picked)->getPosition() + sf::Vector2f(16.f, 8.f);

	TargetInfo.spawnPosition = pos;

	TargetInfo.texture = TextureLoader::getInstance().getTexture(".\\ASSETS\\IMAGES\\Misc\\Target.png");
	newEnemy->init(TargetInfo);

	m_enemies.push_back(newEnemy);
}

void EnemyManager::update()
{
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i)->update();
	}
}

void EnemyManager::checkHits(std::vector<Bullet>& t_bullets)
{
	for (unsigned int bullet = 0; bullet < t_bullets.size(); bullet++)
	{
		if (!t_bullets.at(bullet).active)
			continue;

		for (unsigned int enemy = 0; enemy < m_enemies.size(); enemy++)
		{
			if (!m_enemies.at(enemy)->getActive())
				continue;


			if (m_enemies.at(enemy)->getBounds().intersects(t_bullets.at(bullet).body->getGlobalBounds()))
			{
				if(CollisionDetector::pixelPerfectTest(m_enemies.at(enemy)->getSprite(), t_bullets.at(bullet).body->getSprite()))
				{
					m_enemies.at(enemy)->applyDamage(t_bullets.at(bullet).damage);
					t_bullets.at(bullet).deactivate();
					break;
				}
			}
		}
	}
}
