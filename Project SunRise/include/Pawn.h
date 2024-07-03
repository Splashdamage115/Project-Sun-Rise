#ifndef PAWN_H
#define PAWN_H

#include "Library.h"
#include "InputSwitcher.hpp"

struct newPawnInfo
{
	int level = 0;
	std::shared_ptr<sf::Texture> texture;
	float moveSpeed = 0.f;
	sf::Vector2f spawnPosition = { 0.f,0.f };

	bool lockCamera{ false }; // used for player or any character who will have a camera

	InputType movementType{ InputType::None };
};

class Pawn
{
public:
	virtual void init(newPawnInfo t_pawnInfo) = 0;
	virtual void update() = 0;
	virtual sf::Vector2f getPosition() = 0; // TO DO: not too happy with this

	virtual void moveWithCollision(std::vector<std::shared_ptr<sf::Sprite>>& t_walls) = 0;

	virtual void applyDamage(int t_damage); // this can be overriden if armour is needed (player?)
	virtual sf::FloatRect getBounds() = 0;
	virtual sf::Sprite getSprite() = 0;

	virtual void dead() = 0;

	bool getActive() { return m_active; }
private:

protected:
	bool m_active{ false };
	float m_moveSpeed{ 0.f };

	int m_healthMax{ 10 };
	int m_currentHealth{ 10 };

	bool m_activeCamera{ false };
};

#endif // !PAWN_H
