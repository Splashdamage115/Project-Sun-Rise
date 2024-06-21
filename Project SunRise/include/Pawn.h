#ifndef PAWN_H
#define PAWN_H

#include <SFML/Graphics.hpp>

class Pawn
{
public:
	virtual void update() = 0;
	virtual sf::Vector2f getPosition() = 0; // TO DO: not too happy with this
private:

protected:
	float m_moveSpeed{ 0.f };
};

#endif // !PAWN_H
