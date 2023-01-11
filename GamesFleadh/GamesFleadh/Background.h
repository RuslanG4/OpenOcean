#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>

class Background
{
private:
	sf::Sprite back1;
	sf::Sprite back2;
	sf::Texture backT;
	float speed;
	int width = 0;


public:
	Background();
	Background(const char* t_texture, float t_speed, float t_scaleX, float t_scaleY,float t_width);

	void draw(sf::RenderWindow& window);
	void update();
	void move();
	void increaseSpeed();
};

