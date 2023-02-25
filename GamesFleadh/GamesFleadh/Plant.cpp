#include "Plant.h"

void Plant::render(sf::RenderWindow& window)
{
	window.draw(m_plant);
	window.draw(m_bubble);
	//window.draw(m_box);
}

void Plant::update()
{
	updateHB();
	move();
	animate();
	timeBubbles();
}

void Plant::initialise()
{
	if (!m_texture.loadFromFile(BUBBLES))
	{
		std::cout << "error loading pearl";
	}

	m_bubble.setTexture(m_texture);
	m_bubble.setScale(3, 3);
	m_bubble.setTextureRect(sf::IntRect(0, 0, 23, 40));
	m_bubble.setPosition(sf::Vector2f(offScreenPos));

	if (!m_plantTexture.loadFromFile(PLANT))
	{
		std::cout << "error loading pearl";
	}
	m_plant.setTexture(m_plantTexture);
	m_plant.setPosition(sf::Vector2f(rand() % 800 + 1500, 780));
	m_plant.setScale(2, 2);

	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(3);
}

void Plant::timeBubbles()
{
	if (!bubbleSpawn)
	{
		if (m_plant.getPosition().x < 1350)
		{
			if (bubbleSpawnTimer == 0)
			{
				bubbleSpawnTimer = rand() % 300 + 100;
			}
			bubbleSpawnTimer--;
			if (bubbleSpawnTimer <= 0)
			{
				playBubble();
				m_bubble.setPosition(m_plant.getPosition().x + 30, m_plant.getPosition().y);
				bubbleSpawn = true;
				bubbleTimer = 0;
			}
		}
	}
}

void Plant::updateHB()
{
	pearlHB = new Rectangle(m_bubble.getPosition().x, m_bubble.getPosition().y+32, 64, 64);
	m_box.setPosition(m_bubble.getPosition().x, m_bubble.getPosition().y+32);
}

void Plant::move()
{
	m_bubble.move(-2.5, -2);
	m_plant.move(-2.4, 0);
}

void Plant::animate()
{
	bubbleTimer++;
	if (bubbleTimer > 10)
	{
		bubbleFrame++;
		if (bubbleFrame >= 3) //frame 44 is the last frame the robot is running
		{
			bubbleFrame = 0; //37 is the first frame the robot is running

		}
		bubbleTimer = 0;
	}
	int col = bubbleFrame % 4; //total cols is 5
	int row = 0; //

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 40;
	rectSourceSprite.width = 23;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	m_bubble.setTextureRect(rectSourceSprite);
}

void Plant::playBubble()
{
	if (!bubbleSound.openFromFile("ASSETS\\AUDIO\\bubbles.wav"))
	{
		std::cout << "error laoding music";
	}
	bubbleSound.play();
	bubbleSound.setVolume(20);
}
