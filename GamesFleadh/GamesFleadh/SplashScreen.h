#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include"Defines.h"
#include"Light.h"

class SplashScreen
{
	private:
		int timer = 0;
		sf::Texture backT;
		sf::Sprite backS;

		sf::Texture SquidT;
		sf::Sprite SquidS;

		sf::Texture textT;
		sf::Sprite textS;

		int opacity = 255;

		Light light[3];

		//ANIMATION TIMER AND FRAME
		int squidTimer = 0;
		int squidFrame = 0;

	public:
		void render(sf::RenderWindow& window);
		void initialise();
		void update();

		void animate();
};

