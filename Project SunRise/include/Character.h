#ifndef CHARACTER_H
#define CHARACTER_H

#include "Pawn.h"
#include "Camera.h"

class Character : public Pawn
{
public:
	Character();
	virtual void init(newPawnInfo t_typeInfo)override;
	
	virtual void moveWithCollision(std::vector<std::shared_ptr<sf::Sprite>>& t_walls)override;
	virtual void move()override;
	virtual void setPlayerPosition(std::shared_ptr<sf::Vector2f>& t_player) { m_inputType->setPlayerPointer(t_player); m_inputType->setOwnPosition(m_position); }

	virtual void update()override;
	virtual std::shared_ptr<sf::Vector2f>& getPosition()override { return m_position; }
	virtual sf::FloatRect getBounds()override { return m_body->getGlobalBounds(); }
	virtual sf::Sprite getSprite()override { return *m_body; }

	virtual void dead()override;
private:
	std::shared_ptr<sf::Sprite> m_body;
	std::shared_ptr<sf::Vector2f> m_position;
	std::shared_ptr<sf::CircleShape> m_collisionCircle;
	std::unique_ptr<InputBasic> m_inputType;
	CameraTracker m_followCam;
};

#endif // !CHARACTER_H
