#include "OverLay.h"

void OverLay::render(sf::RenderWindow& window)
{
	window.draw(greyBox[0]);
	window.draw(greyBox[1]);
	window.draw(greyBox[2]);
	window.draw(o2Sprite);
	window.draw(o2percent);
	window.draw(o2Meter);
	window.draw(bar);
	window.draw(pearlAmount);
	window.draw(pearlSprite);
}

void OverLay::update()
{
	getDistance();
	setPearlString();
}

void OverLay::initialise(sf::Font& t_font)
{
	m_font = t_font;
	if (!o2Texture.loadFromFile(O2_SPRITE))
	{
		std::cout << "eror loading 02";
	}
	o2Sprite.setTexture(o2Texture);
	o2Sprite.setScale(1, 1);
	o2Sprite.setPosition(10, 26);

	o2percent.setFont(m_font);
	o2percent.setCharacterSize(48U);
	o2percent.setPosition(WINDOW_WIDTH-164, 26);


	if (!pearlTexture.loadFromFile(PEARL))
	{
		std::cout << "eror loading pearls in overlay";
	}
	pearlSprite.setTexture(pearlTexture);
	//pearlSprite.setScale(1.5, 1.5);
	pearlSprite.setPosition(WINDOW_WIDTH - 62, 102);

	pearlAmount.setFont(m_font);
	pearlAmount.setCharacterSize(48U);
	pearlAmount.setPosition(WINDOW_WIDTH - 164, 85);

	o2Meter.setPosition(60, 42);
	o2Meter.setFillColor(GREEN);
	if (!barTexture.loadFromFile(BAR_SPRITE))
	{
		std::cout << "eror loading 02";
	}
	bar.setTexture(barTexture);
	bar.setScale(2, 2);
	bar.setPosition(42, 26);

	greyBox[0].setSize(sf::Vector2f(150, 40));
	greyBox[0].setFillColor(sf::Color((255, 255, 255, 128)));
	greyBox[0].setPosition(1225, 38);

	greyBox[1].setSize(sf::Vector2f(150, 40));
	greyBox[1].setFillColor(sf::Color((255, 255, 255, 128)));
	greyBox[1].setPosition(1225, 98);

	greyBox[2].setSize(sf::Vector2f(265, 64));
	greyBox[2].setFillColor(sf::Color((255, 255, 255, 128)));
	greyBox[2].setPosition(12, 26);
}

void OverLay::getOxyLevel(float t_oxygen, int t_pearls)
{
	o2Meter.setSize(sf::Vector2f(t_oxygen *2, 15*2));
	pearlCount = t_pearls;
}

void OverLay::getDistance()
{
	if (clock.getElapsedTime().asSeconds() > 0.5)
	{
		distance++;
		clock.restart();
	}
	if (distance < 10)
	{
		o2percent.setString("000" + std::to_string(static_cast<int>(distance)) + "m");
	}
	if (distance >= 10)
	{
		o2percent.setString("00" + std::to_string(static_cast<int>(distance)) + "m");
	}
	if (distance >= 100)
	{
		o2percent.setString("0" + std::to_string(static_cast<int>(distance)) + "m");
	}
	if (distance >= 1000)
	{
		o2percent.setString(std::to_string(static_cast<int>(distance)) + "m");
	}
}

void OverLay::setPearlString()
{
	if (pearlCount < 10)
	{
		pearlAmount.setString("000" + std::to_string(pearlCount));
	}
	if (pearlCount >= 10)
	{
		pearlAmount.setString("00" + std::to_string(pearlCount));
	}
	if (pearlCount >= 100)
	{
		pearlAmount.setString("0" + std::to_string(pearlCount));
	}
	if (pearlCount >= 1000)
	{
		pearlAmount.setString(std::to_string(pearlCount));
	}
}
