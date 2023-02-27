#include "SplashScreen.h"

void SplashScreen::render(sf::RenderWindow& window)
{
	window.draw(s);
}

void SplashScreen::initialise()
{
	if (t.loadFromFile(LOGO))
	{
		std::cout << "error loading splash";

	}
	s.setTexture(t);
}

void SplashScreen::update()
{
	timer++;
	if (timer > 60)
	{
		opacity -= 2;
		s.setColor(sf::Color(255, 255, 255, opacity));
	}
}
