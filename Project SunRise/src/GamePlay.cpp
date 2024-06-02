#include "GamePlay.h"

/// <summary>
/// default constructor
/// </summary>
GamePlay::GamePlay()
{
	spawnTiles();
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

}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void GamePlay::update()
{
	m_player.update();
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void GamePlay::processMouse(sf::Event& t_event)
{
	if(sf::Event::MouseMoved == t_event.type)
	{
		findMousePos(t_event);
	}
	else if (sf::Event::MouseButtonPressed == t_event.type)
	{
		//mouseButtonDown();
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		//mouseButtonUp();
	}
}

void GamePlay::spawnTiles()
{
	RenderObject::getInstance().clearBG();
	m_tiles.clear();

	int xBack = -1;
	std::vector<float> heights;
	float scaleFactor = 1.f;
	int height = 16;
	float width = 32.f;
	
	for (unsigned int i = 0; i < 256; i++)
	{
		if (i % height == 0)
			xBack++;
		std::shared_ptr<sf::Sprite> newTile;
		newTile = std::make_shared<sf::Sprite>();
		newTile->setTexture(TileLookupTable::getInstance().getNumber(1).tileTexture);
		newTile->setScale(scaleFactor, scaleFactor);
		newTile->setPosition(1024.f - ((xBack) * (width * scaleFactor)) + ((i % height) * (width * scaleFactor)), (i % height) * (width / 2.f * scaleFactor) + (xBack * (width / 2.f * scaleFactor)));
		heights.push_back(newTile->getPosition().y);
		m_tiles.push_back(newTile);
	}

	std::sort(heights.begin(), heights.end());

	for (unsigned int u = 0; u < heights.size(); u++)
	{
		for (unsigned int i = 0; i < m_tiles.size(); i++)
		{
			if (m_tiles.at(i)->getPosition().y == heights.at(u))
			{
				RenderObject::getInstance().addBG(m_tiles.at(i));
			}
		}
	}
}
