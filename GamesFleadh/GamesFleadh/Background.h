#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include"Defines.h"
#include"Light.h"

class Background
{
private:
	sf::Sprite back1;
	sf::Sprite back2;
	sf::Texture backT;

	sf::Sprite rocks[8];
	sf::Texture rockTexture;

	sf::Sprite totem;
	sf::Texture totemT;

	const static int numRays = 12;

	Light platLight;

	sf::Sprite plant;

	sf::Sprite platform;
	sf::Texture platT;

	float speed;
	int width = 0;

	int yCo = 0;
	int xCo = 0;

public:
	Background();
	Background(const char* t_texture, float t_speed, float t_scaleX, float t_scaleY,float t_width);
	Background(float t_scaleX, float t_scaleY, float t_x, float t_y, const char* t_texture);

	void draw(sf::RenderWindow& window);
	void update();
	void move();
	void moveRocks();
	void increaseSpeed();
	void moveOtherBG();

	void drawPlants(sf::RenderWindow& window);
	void updatePlants();

};

