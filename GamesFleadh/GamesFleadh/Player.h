#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Events.h"
#include "PlayerState.h"
#include "AnimatedSprite.h"
#include"Defines.h"
#include"Collision.h"
#include<Leap.h>
#include"Light.h"

class Player
{
private:

	Light playerLight;

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

	int totalPearls = 0;

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

	//GETTERS
	sf::Vector2f getVel() { return m_veloctiy; };
	Rectangle* CollisionBox() { return playerHB; };
	bool getAlive() { return isAlive; };
	const sf::Vector2f getPosition() { return m_animated_sprite.getPosition(); };
	float const getOxyLvl() { return oxygenLvl; };
	const int getPearls() { return totalPearls; };

	//SETTERS
	void setVelBack() { pushbackSpeed = 1; };
	void killPlayer() { isAlive = false; }
	void minusOxygen() { lostOxygen = true; }
	void addPearls() { totalPearls++; };

	//PLAYER BOUNDARY
	void boundary();

	//LEAP CONTROLLER
	void moveLEAP(std::string t_action);

	//HIT BOX UPDATER
	void HB();

	//UPDATES OXYGEN AMOUNT
	void updateOxy();

	//IF PLAYER HITS GAME ENTITIES
	void hit(); 
	void bubblesHit()
	{
		oxygenLvl += 15; 
		if (oxygenLvl >100)
		{
			oxygenLvl = 100;
		}
	};
	void mineHit()
	{
		oxygenLvl -= 50;
		pushbackSpeed = 4;
		if (oxygenLvl <= 0)
		{
			oxygenLvl = 0;
		}
	}

	
	
	

};
#endif

