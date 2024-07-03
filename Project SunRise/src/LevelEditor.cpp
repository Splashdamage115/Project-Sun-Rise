#include "LevelEditor.h"
#include "TileLookupTable.h"
#include "GlobalFontStorage.h"
#include "CollisionDetector.h"

/// <summary>
/// default constructor
/// </summary>
LevelEditor::LevelEditor()
{
	// NOTE: reset the level in the constructor
	m_cam.setCameraType(CameraTracker::CameraType::Delayed_Follow);

	m_speedButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("CAMERA SPEED +++"));
	m_speedButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("CAMERA SPEED ---"));

	m_currentEditingLevel = std::make_shared<sf::Text>();

	m_currentEditingLevel->setFont(*GlobalFontStorage::getInstance().getFont());
	m_currentEditingLevel->setString(std::to_string(m_fileToEdit));

	m_currentEditingLevel->setFillColor(sf::Color::White);
	m_currentEditingLevel->setOutlineColor(sf::Color::Black);
	m_currentEditingLevel->setOutlineThickness(0.5f);
	m_currentEditingLevel->setOrigin(m_currentEditingLevel->getGlobalBounds().width / 2.f, m_currentEditingLevel->getGlobalBounds().height / 2.f);
	m_currentEditingLevel->setPosition(140.f, 200.f);

	RenderObject::getInstance().addHUD(m_currentEditingLevel);


	if (!m_arrowTexture.loadFromFile("ASSETS\\IMAGES\\Buttons\\ArrowButton.png")) //rotate_button.png
	{
		DEBUG_MSG("COULDNT FIND BUTTON");
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			m_arrows.push_back(Button());
			m_arrows.at(i).init(m_arrowTexture, sf::Vector2i(64, 64), sf::Vector2f(20.f + (180.f * i), 168.f), 6, 0.5f);
			//m_buttons.at(i).init(m_buttonTexture, sf::Vector2i(256, 128), sf::Vector2f(100.f, 600.f + (150 * i)), 4, 0.5f);
		}
	}
	m_arrows.at(0).changeFrameHeight(1);

	loadTiles();
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

	for (unsigned int i = 0; i < m_arrows.size(); i++)
	{
		m_arrows.at(i).checkBounds(m_mousePos);
		m_arrows.at(i).updateFrame();
	}

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
		for (unsigned int i = 0; i < m_arrows.size(); i++)
			if (m_arrows.at(i).releaseButton())
			{
				if (i == 0)
				{
					m_fileToEdit--;
				}
				else
				{
					m_fileToEdit++;
				}
				if (m_fileToEdit < 1)
					m_fileToEdit = 1;
				if (m_fileToEdit > MAP_AMT)
					m_fileToEdit = MAP_AMT;
				loadTiles();
			}
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		//mouseButtonUp();
		// left mouse, increment level tile (temporary)
		if (t_event.mouseButton.button == sf::Mouse::Left)
		{
			for (int i = m_tiles.size() - 1; i >= 0; i--)
			{
				if (m_tiles.at(i)->getGlobalBounds().contains(m_mousePosGlobal))
				{
					if (m_tiles.at(i)->getGlobalBounds().contains(m_mousePosGlobal))
					{
						if(CollisionDetector::singlePixelTest(*m_tiles.at(i), m_mousePosGlobal))
						{
							m_level.at(i)++;
							if (m_level.at(i) > MAX_TILE_NUM)
								m_level.at(i) = MAX_TILE_NUM;
								break;
						}
					}
				}
			}
		}

		// right mouse, decrement level tile (temporary)
		if (t_event.mouseButton.button == sf::Mouse::Right)
		{
			for (int i = m_tiles.size() - 1; i >= 0; i--)
			{

				if (m_tiles.at(i)->getGlobalBounds().contains(m_mousePosGlobal))
				{
					if (CollisionDetector::singlePixelTest(*m_tiles.at(i), m_mousePosGlobal))
					{
						m_level.at(i)--;
						if (m_level.at(i) <= 0)
							m_level.at(i) = 1;
						break;
					}
				}
			}
		}
		m_levelLoader.writeLevelToFile(m_level, m_fileToEdit);
		loadTiles();
	}
}

void LevelEditor::loadTiles()
{
	m_level = m_levelLoader.readFileToBuffer(m_fileToEdit);
	m_currentEditingLevel->setString(std::to_string(m_fileToEdit));


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
