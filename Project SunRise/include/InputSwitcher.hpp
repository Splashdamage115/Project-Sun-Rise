#ifndef INPUT_SWITCHER_HPP
#define INPUT_SWITCHER_HPP

#include <SFML/Graphics.hpp>
#include "simpleMaths.h"

class InputBasic
{
public:
	virtual sf::Vector2f calculateDisplacement() = 0;
private:

};

class KeyboardInput : public InputBasic
{
public:
	virtual sf::Vector2f calculateDisplacement()override
	{
		sf::Vector2f displacement = sf::Vector2f(0.f,0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			displacement.y -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			displacement.x -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			displacement.y += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			displacement.x += 1.0f;
		}

		// returning a normalised vector
		return displacement;
	}
};

#endif // !INPUT_SWITCHER_HPP
