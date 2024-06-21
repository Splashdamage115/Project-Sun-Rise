#ifndef PLAYER_H
#define PLAYER_H

#include "InputSwitcher.hpp"
#include "Pawn.h"
#include "Camera.h"

class Player : public Pawn
{
public:
	Player();

	virtual void update()override;
	virtual sf::Vector2f getPosition()override { return m_body->getPosition(); }
private:
	std::shared_ptr<sf::Sprite> m_body;
	sf::Texture m_texture;
	std::unique_ptr<InputBasic> m_inputType;
	CameraTracker m_followCam;
};

#endif // !PLAYER_H
