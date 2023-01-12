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
	sf::Vector2f m_position{ 350,200 };
	sf::RectangleShape m_box{ sf::Vector2f(40,80) };
	Rectangle* playerHB;

	const float FRICTION = 0.995;

	float oxygenLvl = 110;
	bool lostOxygen = false;

	bool isMoving = false;

	int pushbackSpeed = 2;

	sf::Clock m_oxyTimer;

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

	void setVel() { pushbackSpeed = 4; };

	void HB();
	void makeIsMoveT() { isMoving = true; pushbackSpeed = 2;
	};
	void hit(); 

	void minusOxygen() { lostOxygen = true; }
	
	void updateOxy();
	float const getOxyLvl() { return oxygenLvl; };

};
#endif

