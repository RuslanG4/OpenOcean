#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include"Defines.h"

class Background
{
private:
	sf::Sprite back1;
	sf::Sprite back2;
	sf::Texture backT;

	sf::Sprite rocks[8];
	sf::Texture rockTexture;

	float speed;
	int width = 0;


public:
	Background();
	Background(const char* t_texture, float t_speed, float t_scaleX, float t_scaleY,float t_width);

	void draw(sf::RenderWindow& window);
	void update();
	void move();
	void moveRocks();
	void increaseSpeed();
};

