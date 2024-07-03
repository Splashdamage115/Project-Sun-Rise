#include "GamePlay.h"
#include "TextureLoader.h"
#include "RenderObject.h"

/// <summary>
/// default constructor
/// </summary>
GamePlay::GamePlay()
{
	m_levelHolder.generateNewLevel();

	newPawnInfo playerInfo;
	playerInfo.level = 0; // player wont have a level system for now
	playerInfo.lockCamera = true;
	playerInfo.movementType = InputType::Keyboard;
	playerInfo.moveSpeed = 300.f;
	playerInfo.spawnPosition = sf::Vector2f(200.f, 200.f);
	playerInfo.texture = TextureLoader::getInstance().getTexture(".\\ASSETS\\IMAGES\\Misc\\Player.png");
	m_player.init(playerInfo);

	m_enemyManager.init();
}

/// <summary>
/// default deconstructor
/// </summary>
GamePlay::~GamePlay()
{
}

/// <summary>
/// resets all values to default as needed
/// </summary>
void GamePlay::resetLevel()
{
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void GamePlay::events(sf::Event& t_event)
{
	if (sf::Event::KeyPressed == t_event.type || sf::Event::KeyReleased == t_event.type) //user pressed a key
	{
		processKeys(t_event);
	}
	else
	{
		processMouse(t_event);
	}
}

/// !!!---Private function---!!!
/// <summary>
/// process any input from the user
/// </summary>
/// <param name="t_event">use this for the key press</param>
void GamePlay::processKeys(sf::Event& t_event)
{
	if (sf::Keyboard::Space == t_event.key.code)
	{
		m_enemyManager.spawnNewEnemy(m_levelHolder.getTiles(m_player.getPosition()));
	}
}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void GamePlay::update()
{
	m_player.update();
	m_player.moveWithCollision(m_levelHolder.getColliders());
	m_bulletManager.updateBullets();
	m_enemyManager.update();
	m_enemyManager.checkHits(m_bulletManager.getBulets());
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void GamePlay::processMouse(sf::Event& t_event)
{
	if(sf::Event::MouseMoved == t_event.type)
	{
		findMousePos(t_event);
		findMousePosGlobal(t_event);
	}
	else if (sf::Event::MouseButtonPressed == t_event.type)
	{
		//mouseButtonDown();
		
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		//mouseButtonUp();

		float spreadAmt = 30.f; // the amount the bullets spread
		m_bulletManager.initNewBullet(m_player.getPosition(), m_mousePosGlobal, spreadAmt);
	}
}
