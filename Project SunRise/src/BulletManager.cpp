#include "BulletManager.h"

BulletManager::BulletManager()
{
	// will need to load all bullets here somehow
	sf::Texture newTexture;
	newTexture.loadFromFile(".\\ASSETS\\IMAGES\\Misc\\BulletAnimBasic.png");
	m_bulletTextures.push_back(newTexture);
}

// implement spread here somehow
void BulletManager::initNewBullet(sf::Vector2f t_pawnPos, sf::Vector2f t_aimPos, float t_spread)
{
	// implement check if any bullets are available to be pushed back into
	float moveSpeed = 1000.f;

	std::shared_ptr<AnimatedSprite> bulletSprite;
	
	// sort out what sprite is required by the gun here
	bulletSprite = std::make_shared<AnimatedSprite>(0.1f, m_bulletTextures.at(0));
	// frames for the bullet animation
	bulletSprite->addFrame(sf::IntRect(0, 0, 16, 16));
	bulletSprite->addFrame(sf::IntRect(16, 0, 16, 16));
	bulletSprite->addFrame(sf::IntRect(32, 0, 16, 16));
	bulletSprite->addFrame(sf::IntRect(48, 0, 16, 16));
	bulletSprite->addFrame(sf::IntRect(64, 0, 16, 16));

	Bullet newBullet;
	newBullet.init(t_pawnPos, t_aimPos, moveSpeed, bulletSprite, t_spread);
	m_bullets.push_back(newBullet);
}

void BulletManager::updateBullets()
{
	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets.at(i).update();
	}
}
