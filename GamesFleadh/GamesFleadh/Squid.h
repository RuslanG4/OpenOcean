#pragma once
#include <SFML/Graphics.hpp>
#include"Defines.h"
#include"Collision.h"
#include<iostream>
#include"Thor/Vectors.hpp"
#include"Light.h"
#include<math.h>

class Squid
{
private:
	float speed = 1;

	//Light
	Light light;

	//hitbox
	Rectangle* hb;
	sf::RectangleShape m_box;

	//SQUID AND OUTLINE SPRITES
	sf::Sprite squid;
	sf::Sprite squidBlackedOut;
	sf::Texture squidT;

	//sf::RectangleShape m_box{ sf::Vector2f(54,49) };
	//Rectangle* fishHB;

	//POSITIONS AND VELOCITY
	sf::Vector2f BlackedOutposition{ 100,500 };
	sf::Vector2f position{ 0,0};
	sf::Vector2f velocity{ 2,0 };

	//ANIMATION TIMER AND FRAME
	int squidTimer = 0;
	int squidFrame = 0;

	//SPRITE SCALE
	float scale = 0.5;

	//BIG SQUID MOVEMNT
	sf::Vector2f chaseDirection;

	//SPAWNS BIG SQUID
	bool start = false;
	//IF SQUID HAS DONE ITS ENTERANCE
	bool enterance = false;
	//IF SQUID IS MOVING
	bool isMoving = false;

	//TIMER FOR DECISION 
	int aiTimer = 0;
	//CHOICE OF ACTION
	int aiChoice = 0;
	//SPIN INDICATES DASH
	int spinTimer = 90;
	//AMOUNT OF TIMES SQUID HAS DASHED, MAX 2
	int dashAmount = 0;

public:
	//SQUID OUTLINE METHODS
	void update(sf::Vector2f t_playerPos);
	void loadTextures();
	void render(sf::RenderWindow& t_window);
	void animate();
	void move();
	void Scale();

	//SQUID BOSS METHODS
	void bossEntrance(sf::Vector2f playerPos);
	void aiMove(sf::Vector2f playerPos);
	void dash();
	void reset();

	//GETTERS
	int returnDashes() { return dashAmount; };
	sf::Sprite getBsquid() { return squidBlackedOut; };
	float getScale() { return scale; };
	Rectangle* getHB() { return hb; };
	Light getLight() { return light; };

};

