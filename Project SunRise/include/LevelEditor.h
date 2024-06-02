// This class is used for the level editor
#ifndef LEVEL_EDITOR_H
#define LEVEL_EDITOR_H

#include "GameMode.h"
#include "LevelLoader.h"
#include "Camera.h"
#include "SimpleButton.h"

class LevelEditor : public GameMode
{
public:
	LevelEditor();  // standard constructor
	~LevelEditor(); // standard deconstructor (shouldnt be used)

	virtual void resetLevel();                         // used to reset the level for each session instead of reconstructing
	virtual void events(sf::Event& t_event);           // used to handle all new events outside key presses
	virtual void update();         // all update events

private:
	virtual void processKeys(sf::Event& t_event);      // handles all key inputs
	virtual void processMouse(sf::Event& t_event);     // handles all mouse events

	void loadTiles();

	std::vector<std::shared_ptr<sf::Sprite>> m_tiles;
	std::vector<int> m_level;
	LevelLoader m_levelLoader;
	float m_cameraSpeed = 10.f;

	sf::Vector2f m_camPos{ 0.f,0.f };
	CameraTracker m_cam;
	std::vector<std::shared_ptr<SimpleButton>> m_speedButtons;
};

#endif // !LEVEL_EDITOR_H