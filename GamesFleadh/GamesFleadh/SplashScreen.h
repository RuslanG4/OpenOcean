#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include"Defines.h"

class SplashScreen
{
	private:
		int timer = 0;
		sf::Texture t;
		sf::Sprite s;
		int opacity = 255;

	public:
		void render(sf::RenderWindow& window);
		void initialise();
		void update();
};

