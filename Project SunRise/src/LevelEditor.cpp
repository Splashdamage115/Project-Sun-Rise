#include "LevelEditor.h"
#include "TileLookupTable.h"

/// <summary>
/// default constructor
/// </summary>
LevelEditor::LevelEditor()
{
	// NOTE: reset the level in the constructor
	loadTiles();
	m_cam.setCameraType(CameraTracker::CameraType::Delayed_Follow);

	m_speedButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("CAMERA SPEED +++"));
	m_speedButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("CAMERA SPEED ---"));
}

/// <summary>
/// default deconstructor
/// </summary>
LevelEditor::~LevelEditor()
{
}

/// <summary>
/// resets all values to default as needed
/// </summary>
void LevelEditor::resetLevel()
{
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void LevelEditor::events(sf::Event& t_event)
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
void LevelEditor::processKeys(sf::Event& t_event)
{

}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void LevelEditor::update()
{
	// change the camera speed based off top right buttons
	if (m_speedButtons.at(0)->clicked())
		m_cameraSpeed++;
	if (m_speedButtons.at(1)->clicked())
		m_cameraSpeed--;

	// move around the camera
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_camPos.y -= m_cameraSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_camPos.y += m_cameraSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_camPos.x -= m_cameraSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_camPos.x += m_cameraSpeed;
	m_cam.update(m_camPos);
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void LevelEditor::processMouse(sf::Event& t_event)
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
		for (int i = m_tiles.size() - 1; i >= 0; i--)
		{
			if (m_tiles.at(i)->getGlobalBounds().contains(m_mousePosGlobal))
			{
				m_level.at(i)++;
				break;
			}
		}
		m_levelLoader.writeLevelToFile(m_level);
		loadTiles();
	}
}

void LevelEditor::loadTiles()
{
	m_level = m_levelLoader.readFileToBuffer();


	RenderObject::getInstance().clearBG();
	m_tiles.clear();

	int xBack = -1;
	std::vector<float> heights;
	float scaleFactor = 1.f;
	int height = 16;
	float width = 90.f;

	for (unsigned int i = 0; i < 256; i++)
	{
		if (i % height == 0)
			xBack++;
		std::shared_ptr<sf::Sprite> newTile;
		newTile = std::make_shared<sf::Sprite>();
		newTile->setTexture(TileLookupTable::getInstance().getNumber(m_level.at(i)).tileTexture);
		newTile->setOrigin(newTile->getGlobalBounds().width / 2.f, newTile->getGlobalBounds().height / 2.f);
		newTile->setScale(scaleFactor, scaleFactor);
		newTile->setPosition(1024.f - ((xBack) * (width * scaleFactor)) + ((i % height) * (width * scaleFactor)), (i % height) * (width / 2.f * scaleFactor) + (xBack * (width / 2.f * scaleFactor)));
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
