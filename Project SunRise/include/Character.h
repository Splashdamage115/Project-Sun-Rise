#ifndef CHARACTER_H
#define CHARACTER_H

#include "Pawn.h"
#include "Camera.h"

class Character : public Pawn
{
public:
	Character();
	virtual void init(newPawnInfo t_typeInfo)override;


	virtual void update()override;
	virtual sf::Vector2f getPosition()override { return m_body->getPosition(); }
	virtual sf::FloatRect getBounds()override { return m_body->getGlobalBounds(); }
	virtual sf::Sprite getSprite()override { return *m_body; }

	virtual void dead()override;
private:
	std::shared_ptr<sf::Sprite> m_body;
	std::unique_ptr<InputBasic> m_inputType;
	CameraTracker m_followCam;
};

#endif // !CHARACTER_H
