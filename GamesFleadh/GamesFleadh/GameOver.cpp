#include "GameOver.h"

void GameOver::render(sf::RenderWindow& window)
{
	window.draw(biggerBox);
	window.draw(box);
	
	if (drawnBox)
	{
		window.draw(m_text);
		window.draw(m_gameOverText);
		window.draw(m_distanceText);
	}
}

void GameOver::update()
{
	m_text.setString(std::to_string(restartTimer));
	if (!drawnBox)
	{
		animateGameOver();
	}
	else
	{
		updateTimer();
	}
}

void GameOver::initialise(sf::Font& t_font)
{
	m_font = t_font;
	m_text.setFont(m_font);
	m_text.setCharacterSize(164U);
	m_text.setPosition(895, 450);

	m_gameOverText.setString("GAME OVER");
	m_gameOverText.setFont(m_font);
	m_gameOverText.setCharacterSize(104U);
	m_gameOverText.setPosition(715, 315);

	m_distanceText.setFont(m_font);
	m_distanceText.setCharacterSize(48U);
	m_distanceText.setPosition(535, 435);

	box.setFillColor(DEEPGREEN);
	box.setSize(sf::Vector2f(WINDOW_WIDTH, sizeIncrease));
	box.setOrigin(0, sizeIncrease / 2);
	box.setPosition(0, WINDOW_HEIGHT / 2);


	biggerBox.setFillColor(sf::Color(26, 8, 0, 128));
	biggerBox.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
	biggerBox.setPosition(0,0);
}

void GameOver::updateTimer()
{
	clock++;
	if (clock >= 60)
	{
		restartTimer--;
		if (restartTimer == 0)
		{
			restarted = true;
			restartTimer = 3;
		}
		clock = 0;;
	}
}

void GameOver::animateGameOver()
{
	//boxTimer++;
	//if (boxTimer > 5)
	//{
		sizeIncrease += 10;
		//xPos += 5;
		if (sizeIncrease > 300)
		{
			drawnBox = true;
		//	boxTimer = 0;
		}
		box.setOrigin(xPos, sizeIncrease / 2);
		box.setSize(sf::Vector2f(WINDOW_WIDTH, sizeIncrease));
		
		//boxTimer = 0;
	//}
}

void GameOver::getDistance(int t_distance)
{
	distance = t_distance;
	m_distanceText.setString("You   travelled   " + std::to_string(distance) + "m   before   drowning");
}
