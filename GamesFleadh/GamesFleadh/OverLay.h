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

	sf::Sprite pearlSprite;
	sf::Texture pearlTexture;

	sf::RectangleShape greyBox[3];

	sf::Text pearlAmount;
	//FONT
	sf::Font m_font;

	int miliseconds = 120;

	//VARIBALES FOR ENTITIES
	int distance = 0;
	sf::Clock clock;
	int coins = 0;

	//
	int healthTime = 0;
	int healthFrame = 0;

	int pearlCount = 0;

	sf::Text mileStone;

	bool flash = true;


	int flashTimer = 0;

	int beginFlashTimer = 0;

	bool startFlash = false;

	
	
	int Mile = 50;

public:
	void render(sf::RenderWindow& window);
	void update();
	void initialise(sf::Font& t_font);
	void getOxyLevel(float t_oxygen, int t_pearls);
	void getDistance();
	void reset() { distance = 0; };
	int returnDistance() { return distance; };
	void setPearlString();
	void flashing();
	void moveMileStone();
};

