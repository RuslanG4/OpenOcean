#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Events.h"
#include "PlayerState.h"
#include "AnimatedSprite.h"
#include"Defines.h"
#include"Collision.h"

class Player
{
private:
	PlayerState* m_state;
	AnimatedSprite m_animated_sprite;

	sf::Vector2f m_veloctiy;
	sf::Vector2f m_position{ 200,200 };
	sf::RectangleShape m_box{ sf::Vector2f(40,80) };
	Rectangle* playerHB;

	const float FRICTION = 0.995;

public:
	//FSM
	Player(const AnimatedSprite&);
	virtual void handleInput(gpp::Events);
	virtual void update();
	AnimatedSprite& getAnimatedSprite();
	AnimatedSprite& getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite&);
	PlayerState* getPlayerState();
	void setPlayerState(PlayerState*);
	void render(sf::RenderWindow& window);

	sf::Vector2f getVel() { return m_veloctiy; };
	Rectangle* CollisionBox() { return playerHB; };
	float vectorLengthSquared();
	void move();
	void boundary();

	void setVel() { m_veloctiy.x = m_veloctiy.x * 0.5; m_veloctiy.y = m_veloctiy.y * 0.5; };

	void HB();
	void makeIsMoveT() { isMoving = true; };
	void makeIsMoveF() { isMoving = false; };
	bool isMoving = false;

};
#endif

