#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Events.h"
#include "PlayerState.h"
#include "AnimatedSprite.h"
#include"Defines.h"
#include"Collision.h"
#include<Leap.h>

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

	float oxygenLvl = 100;
	bool lostOxygen = false;

	bool isAlive = true;

	int pushbackSpeed = 1;

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
	bool getAlive() { return isAlive; };
	float vectorLengthSquared();
	void boundary();
	const sf::Vector2f getPosition() { return m_animated_sprite.getPosition(); };

	void killPlayer() { isAlive = false; }

	void moveLEAP(std::string t_action);

	void setVelBack() { pushbackSpeed = 1; };

	void HB();
	void hit(); 

	void mineHit() {
		oxygenLvl -= 50;
		pushbackSpeed = 4;
	}

	void minusOxygen() { lostOxygen = true; }
	
	void updateOxy();
	float const getOxyLvl() { return oxygenLvl; };

};
#endif

