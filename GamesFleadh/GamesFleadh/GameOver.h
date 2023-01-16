#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include"Defines.h"

class GameOver
{
private:

	
	sf::Text m_text;
	sf::Text m_gameOverText;
	sf::Text m_distanceText;
	//FONT
	sf::Font m_font;

	sf::RectangleShape box;
	sf::RectangleShape biggerBox;
	int boxTimer = 0;

	int restartTimer = 3;;

	int clock=0;

	int sizeIncrease = 30;

	int xPos = 0;

	bool restarted = false;
	bool drawnBox = false;

public:
	void render(sf::RenderWindow& window);
	void update();
	void initialise(sf::Font& t_font);
	void updateTimer();
	bool const getRestart() { return restarted; };
	void setRestartFalse() {
	restarted = false;
	drawnBox = false;
	sizeIncrease = 30;
	box.setSize(sf::Vector2f(WINDOW_WIDTH, sizeIncrease));
	box.setOrigin(0, sizeIncrease / 2);
	box.setPosition(0, WINDOW_HEIGHT / 2);
	};
	void animateGameOver();

};

