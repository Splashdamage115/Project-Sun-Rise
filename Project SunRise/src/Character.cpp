#include "Character.h"
#include "Game.h"
#include "RenderObject.h"
#include "Movement.h"

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

	m_collisionCircle = std::make_shared<sf::CircleShape>();

	m_collisionCircle->setRadius(25.f);
	m_collisionCircle->setPosition(t_typeInfo.spawnPosition);
	m_collisionCircle->setOrigin(m_collisionCircle->getRadius(), m_collisionCircle->getRadius());
	m_collisionCircle->setFillColor(sf::Color::Transparent);
	m_collisionCircle->setOutlineColor(sf::Color::Cyan);
	m_collisionCircle->setOutlineThickness(1.f);


	m_body->setTexture(*t_typeInfo.texture);
	m_body->setPosition(t_typeInfo.spawnPosition);
	m_body->setOrigin(m_collisionCircle->getRadius(), m_collisionCircle->getRadius() + 10.f);

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

	
	RenderObject::getInstance().add(m_collisionCircle);
	 
}

void Character::moveWithCollision(std::vector<std::shared_ptr<sf::Sprite>>& t_walls)
{
	if (m_active)
	{
		Movement cols; // Ensure Movement class is correctly implemented
		sf::Vector2f movement = m_inputType->calculateDisplacement() * m_moveSpeed * Game::deltaTime;
		sf::Vector2f position = m_body->getPosition();

		// Ensure calculateIntersects returns the corrected movement vector
		sf::Vector2f newMovement = cols.calculateIntersects(t_walls, position, 25.f, movement);

		// Move the character and collision circle with the corrected movement
		m_body->move(newMovement);
		m_collisionCircle->move(newMovement);
	}
}

void Character::update()
{
	if (m_active)
	{
		if(m_activeCamera)
			m_followCam.update(m_body->getPosition());
	}
}

void Character::dead()
{
	m_active = false;
	m_body->setPosition(sf::Vector2f(-200000.f, -200000.f));
}
