#include "Plant.h"

void Plant::render(sf::RenderWindow& window)
{
	window.draw(plantLight.draw());
	window.draw(m_plant);
	window.draw(bubbleLight.draw());
	window.draw(m_bubble);
	window.draw(m_text);
	//window.draw(m_box);
}

void Plant::update()
{
	updateHB();
	move();
	animate();
	timeBubbles();

	if (startMove)
	{
		moveText();
	}
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
	m_plant.setPosition(sf::Vector2f(WINDOW_WIDTH, (WINDOW_HEIGHT - 170)));
	m_plant.setScale(2, 2);

	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(3);

	plantLight = Light{sf::Vector2f( m_plant.getPosition().x +55,m_plant.getPosition().y + 60 )};// m_plant.getPosition()};

	plantLight.scale(0.75, 0.75);
	plantLight.setMaxLight(132);

	bubbleLight = Light{ sf::Vector2f(m_plant.getPosition().x + 55,m_plant.getPosition().y + 60) };// m_plant.getPosition()};
	bubbleLight.setMaxLight(108);
	bubbleLight.selectColour(sf::Color(153, 255, 255), sf::Color(0, 102, 102));


	if (!font.loadFromFile(FONT))
	{
		std::cout << "error loading font";
	}
	m_text.setFont(font);
	m_text.setCharacterSize(40U);
	m_text.setString("H2O");
	m_text.setPosition(-400, 400);
	m_text.setFillColor(sf::Color(255, 227, 248, 255));

	
}

void Plant::setPosition()
{
	m_plant.setPosition(sf::Vector2f((rand() % 600) + (WINDOW_WIDTH + 100), (WINDOW_HEIGHT - 170)));
	plantLight = Light{ sf::Vector2f(m_plant.getPosition().x + 55,m_plant.getPosition().y + 60) };
	plantLight.scale(0.75, 0.75);
	bubbleSpawn = false; 
}

void Plant::timeBubbles()
{
	if (!bubbleSpawn)
	{
		if (m_plant.getPosition().x < 1750)
		{
			if (bubbleSpawnTimer == 0)
			{
				bubbleSpawnTimer = rand() % 200 + 100;
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
	bubbleLight.setCenter(sf::Vector2f(m_bubble.getPosition().x+35, m_bubble.getPosition().y+55));
	bubbleLight.scale(0.3, 0.3);

	m_bubble.move(-2.5, -2);
	m_plant.move(-3.6, 0);
	plantLight.moveLight(-3.6, 0);
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

void Plant::setText()
{
	startMove = true;
	m_text.setPosition(m_bubble.getPosition());
}

void Plant::moveText()
{
	m_text.move(-2.4, -3.4);


	if (m_text.getPosition().y < -50)
	{
		m_text.setPosition(1300, 1080);
		startMove = false;
	}
}
