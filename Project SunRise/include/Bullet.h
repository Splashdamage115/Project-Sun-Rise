#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"

struct Bullet
{
public:
	bool active;
	std::shared_ptr<AnimatedSprite> body;
	sf::Vector2f displacement;

	Bullet();
	void init(sf::Vector2f t_start, sf::Vector2f t_aim, float t_bulletSpeed, std::shared_ptr<AnimatedSprite> t_body, float t_spread);
	void update();
	sf::Vector2f getPos();
};

#endif // !BULLET_H
