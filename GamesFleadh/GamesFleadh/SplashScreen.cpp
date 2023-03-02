#include "SplashScreen.h"

void SplashScreen::render(sf::RenderWindow& window)
{

	window.draw(backS);
	for (int i = 0; i < 3; i++)
	{
		window.draw(light[i].draw());
	}
	window.draw(SquidS);
	window.draw(textS);
}

void SplashScreen::initialise()
{
	if (textT.loadFromFile(TEXT))
	{
		std::cout << "error loading splash";

	}
	textS.setTexture(textT);


	if (backT.loadFromFile(LOADINGBG))
	{
		std::cout << "error loading splash";

	}
	backS.setTexture(backT);

	if (SquidT.loadFromFile("ASSETS\\IMAGES\\ColossalSquid.png"))
	{
		std::cout << "error loading splash";

	}
	SquidS.setTexture(SquidT);
	SquidS.setOrigin(155, 96);
	SquidS.setScale(2, 2);
	SquidS.setPosition(2020,300);
	SquidS.setTextureRect(sf::IntRect(0, 0, 310, 192));
	//SquidS.setRotation(270);
	SquidS.setColor(sf::Color((255, 0, 255, 165)));



	light[0] = Light{ sf::Vector2f(300,120) };
	light[1] = Light{ sf::Vector2f(1430,280) };
	light[2] = Light{ sf::Vector2f(1000,800) };

	for (int i = 0; i < 3; i++)
	{
		light[i].setMaxLight(255);
		light[i].setIntensity(0.5);
		light[i].scale(2, 2);
	}
	light[0].selectColour(sf::Color(153, 255, 255), sf::Color(0, 102, 102));
	light[1].selectColour(sf::Color(153, 51, 255), sf::Color(153, 255, 255));
	light[2].selectColour(sf::Color(153, 255, 255), sf::Color(204, 153, 255));
}

void SplashScreen::update()
{
	animate();
	timer++;
	if (timer > 60)
	{
		opacity -= 2;
		if (opacity <= 0)
		{
			opacity = 0;
		}
		textS.setColor(sf::Color(255, 255, 255, opacity));
	}

	SquidS.setPosition(sf::Vector2f(SquidS.getPosition().x, SquidS.getPosition().y + -(float)std::cos(SquidS.getPosition().x / 200) * 5));
	SquidS.move(-8, 0);
}

void SplashScreen::animate()
{
	squidTimer++;
	if (squidTimer > 4)
	{
		squidFrame++;
		if (squidFrame > 11) //frame 44 is the last frame the robot is running
		{
			squidFrame = 0; //37 is the first frame the robot is running
		}
		squidTimer = 0;
	}
	int col = 0;
	int row = squidFrame % 11;

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 192;
	rectSourceSprite.width = 310;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	SquidS.setTextureRect(rectSourceSprite);
	
}
