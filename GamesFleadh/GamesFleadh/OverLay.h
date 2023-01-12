#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include"Defines.h"
class OverLay
{
private:
	//02
	sf::Sprite o2Sprite;
	sf::Texture o2Texture;

	sf::Sprite bar;
	sf::Texture barTexture;

	sf::RectangleShape o2Meter;
	//TEXT FOR AMOUNT
	sf::Text o2percent;
	//FONT
	sf::Font m_font;

	int miliseconds = 120;

	//VARIBALES FOR ENTITIES
	int score = 0;
	int coins = 0;

	//
	int healthTime = 0;
	int healthFrame = 0;


public:
	void render(sf::RenderWindow& window);
	void update();
	void initialise(sf::Font& t_font);
	void getOxyLevel(float t_oxygen);
};

