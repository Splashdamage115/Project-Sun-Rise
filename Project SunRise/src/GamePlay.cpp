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
	m_bulletManager.updateBullets();
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

// TO DO:  MOVE TO A NEW FILE
void GamePlay::spawnTiles()
{
	LevelLoader levelLoader;
	std::vector<int>level = levelLoader.readFileToBuffer(rand() % MAP_AMT + 1);


	RenderObject::getInstance().clearBG();
	m_tiles.clear();

	int xBack = -1;
	std::vector<float> heights;
	float scaleFactor = 1.f;
	int height = 16;
	float width = 62.f;

	int xBackBig = -1;
	int heightBig = 4; // height of tiles on the diagonal (how many level tiles will spawn)
	float widthBig = 2048.f; // change this to change distance between tile sets
	float xOffset = 0.f;
	float yOffset = 0.f;
	
	// 16 is the amount of level tiles spawned
	for(unsigned int u = 0; u < 16; u++)
	{
		if (u % heightBig == 0)
			xBackBig++;

		xOffset = -((xBackBig) * (widthBig)) + ((u % heightBig) * (widthBig));
		yOffset = (u % heightBig) * (widthBig / 2.f) + (xBackBig * (widthBig / 2.f));

		level = levelLoader.readFileToBuffer(rand() % 7 + 1);

		for (unsigned int i = 0; i < 256; i++)
		{
			if (i % height == 0)
				xBack++;
			std::shared_ptr<sf::Sprite> newTile;
			newTile = std::make_shared<sf::Sprite>();
			newTile->setTexture(TileLookupTable::getInstance().getNumber(level.at(i)).tileTexture);
			newTile->setOrigin(newTile->getGlobalBounds().width / 2.f, newTile->getGlobalBounds().height / 2.f);
			newTile->setScale(scaleFactor, scaleFactor);
			newTile->setPosition(xOffset - ((xBack) * (width * scaleFactor)) + ((i % height) * (width * scaleFactor)), yOffset + (i % height) * (width / 2.f * scaleFactor) + (xBack * (width / 2.f * scaleFactor)));
			bool addNew = true;
			for (unsigned int u = 0; u < heights.size(); u++)
			{
				if (newTile->getPosition().y == heights.at(u))
				{
					addNew = false;
					break;
				}
			}
			if (addNew)
				heights.push_back(newTile->getPosition().y);
			m_tiles.push_back(newTile);
		}
		xBack = -1;
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
