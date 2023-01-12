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
	o2percent.setCharacterSize(32U);
	o2percent.setPosition(64, 64);

	o2Meter.setPosition(60, 42);
	o2Meter.setFillColor(sf::Color::Green);
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
	//o2percent.setString(std::to_string(static_cast<int>(t_oxygen)) + "%");
}
