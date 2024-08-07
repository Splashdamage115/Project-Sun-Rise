#ifndef INPUT_SWITCHER_HPP
#define INPUT_SWITCHER_HPP

#include "Library.h"
#include "simpleMaths.h"

enum class InputType
{
	None, Keyboard, RunTowardsPlayer
};

class InputBasic
{
public:
	virtual sf::Vector2f calculateDisplacement() = 0;
	virtual void setPlayerPointer(std::shared_ptr<sf::Vector2f>& t_player) { ;/*Dont set*/ }
	virtual void setOwnPosition(std::shared_ptr<sf::Vector2f>& t_pos) { ;/*Dont set*/ }
private:

};

class NoneInput : public InputBasic
{
public:
	virtual sf::Vector2f calculateDisplacement()override
	{
		return sf::Vector2f(0.f, 0.f); // you dont move at all
	}
private:

};

class RunTowardsPlayer : public InputBasic
{
public:
	virtual sf::Vector2f calculateDisplacement()override
	{
		return math::displacement(*m_position.lock(), *m_playerPosition.lock());
	}
	void setPlayerPointer(std::shared_ptr<sf::Vector2f>& t_player)override {
		m_playerPosition = t_player;
	}
	void setOwnPosition(std::shared_ptr<sf::Vector2f>& t_pos)override {
		m_position = t_pos;
	}
private:
	std::weak_ptr<sf::Vector2f> m_playerPosition;
	std::weak_ptr<sf::Vector2f> m_position;
};

class KeyboardInput : public InputBasic
{
public:
	virtual sf::Vector2f calculateDisplacement()override
	{
		sf::Vector2f displacement = sf::Vector2f(0.f,0.f);

		int clickedAmt = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			displacement.y -= 1.0f;
			clickedAmt++;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			displacement.x -= 1.0f;
			clickedAmt++;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			displacement.y += 1.0f;
			clickedAmt++;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			displacement.x += 1.0f;
			clickedAmt++;
		}

		// change it to a square root, so that movement is linear in all directions
		if(clickedAmt >= 2)
		{
			displacement.x /= 1.4142f;
			displacement.y /= 1.4142f;
		}

		// returning a normalised vector
		return displacement;
	}
};

#endif // !INPUT_SWITCHER_HPP
