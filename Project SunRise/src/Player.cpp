#include "Player.h"
#include "Game.h"
#include "RenderObject.h"

Player::Player()
{
	m_moveSpeed = 300.f;

	m_body = std::make_shared<sf::Sprite>();

	//m_body->setFillColor(sf::Color::Cyan);
	m_texture.loadFromFile(".\\ASSETS\\IMAGES\\Misc\\Player.png");
	m_body->setTexture(m_texture);
	m_body->setPosition(200.f, 200.f);

	RenderObject::getInstance().add(m_body);

	m_inputType = std::make_unique<KeyboardInput>();
}

void Player::update()
{
	m_body->move(m_inputType->calculateDisplacement() * m_moveSpeed * Game::deltaTime);
}
