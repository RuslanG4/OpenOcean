#include "OverLay.h"

void OverLay::render(sf::RenderWindow& window)
{
	window.draw(o2Sprite);
	window.draw(o2percent);
	window.draw(o2Meter);
	window.draw(bar);
}

void OverLay::update()
{
	getDistance();
}

void OverLay::initialise(sf::Font& t_font)
{
	m_font = t_font;
	if (!o2Texture.loadFromFile(O2_SPRITE))
	{
		std::cout << "eror loading 02";
	}
	o2Sprite.setTexture(o2Texture);
	o2Sprite.setScale(1.5, 1.5);
	o2Sprite.setPosition(0, 0);

	o2percent.setFont(m_font);
	o2percent.setCharacterSize(48U);
	o2percent.setPosition(WINDOW_WIDTH-164, 26);

	o2Meter.setPosition(60, 42);
	o2Meter.setFillColor(GREEN);
	if (!barTexture.loadFromFile(BAR_SPRITE))
	{
		std::cout << "eror loading 02";
	}
	bar.setTexture(barTexture);
	bar.setScale(2, 2);
	bar.setPosition(42, 26);
}

void OverLay::getOxyLevel(float t_oxygen)
{
	o2Meter.setSize(sf::Vector2f(t_oxygen *2, 15*2));
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
