#include "Character.h"
#include "Game.h"
#include "RenderObject.h"

Character::Character()
{
}

void Character::init(newPawnInfo t_typeInfo)
{
	m_active = true;
	m_moveSpeed = t_typeInfo.moveSpeed; // player = 300.f

	m_body = std::make_shared<sf::Sprite>();

	//m_bPlayerody->setFillColor(sf::Color::Cyan);
	//m_texture.loadFromFile(".\\ASSETS\\IMAGES\\Misc\\Player.png");

	m_body->setTexture(*t_typeInfo.texture);
	m_body->setPosition(t_typeInfo.spawnPosition);
	m_body->setOrigin(m_body->getGlobalBounds().width, m_body->getGlobalBounds().height);

	RenderObject::getInstance().add(m_body);

	// setup input type /  movement type for the npc/player
	switch (t_typeInfo.movementType)
	{
	case InputType::None:
		m_inputType = std::make_unique<NoneInput>();
		break;
	case InputType::Keyboard:
		m_inputType = std::make_unique<KeyboardInput>();
		break;
	default:
		m_inputType = std::make_unique<NoneInput>();
		break;
	}

	m_activeCamera = t_typeInfo.lockCamera;

	if (m_activeCamera)
		m_followCam.setCameraType(CameraTracker::CameraType::Delayed_Follow);
}

void Character::update()
{
	if (m_active)
	{
		m_body->move(m_inputType->calculateDisplacement() * m_moveSpeed * Game::deltaTime);
		if(m_activeCamera)
			m_followCam.update(m_body->getPosition());
	}
}

void Character::dead()
{
	m_active = false;
	m_body->setPosition(sf::Vector2f(-200000.f, -200000.f));
}
