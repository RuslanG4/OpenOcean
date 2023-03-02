#include "Fish.h"

void Fish::update(sf::Vector2f t_playerPos)
{
	animate();
	move();
	boundary();

	//if (startMove)
	//{
		moveText();
	//}
}

void Fish::loadTextures()
{
	if (!m_texture.loadFromFile(FISH_SPRITES))
	{
		std::cout << "error loading fish";
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(-2, 2);
	m_sprite.setOrigin(16, 16);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_sprite.setPosition(rand() % 300 + (WINDOW_WIDTH + 200), rand() % (WINDOW_HEIGHT - 150) + 100);

	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(3);


	light = Light{ sf::Vector2f(500,300) };
	light.setMaxLight(255);
	light.setIntensity(0.5);
	light.selectColour(sf::Color(0, 0, 0), sf::Color(128, 128, 128));


	if (!font.loadFromFile(FONT))
	{
		std::cout << "error loading font";
	}
	for (int i = 0; i < 3; i++)
	{
		m_text[i].setFont(font);
		m_text[i].setCharacterSize(40U);
		m_text[i].setString("5");
		m_text[i].setPosition(-400, -400);
		m_text[i].setFillColor(sf::Color(159, 42, 76));
	}
}
void Fish::animate()
{
	{
		fishTimer++;
		if (fishTimer > 5)
		{
			fishFrame++;
			if (fishFrame > 4) //frame 44 is the last frame the robot is running
			{
				fishFrame = 0; //37 is the first frame the robot is running
			}
			fishTimer = 0;
		}
		int col = fishFrame % 4; //total cols is 5
		int row = 0; //

		sf::IntRect rectSourceSprite;
		rectSourceSprite.height = 32;
		rectSourceSprite.width = 32;
		rectSourceSprite.left = col * rectSourceSprite.width;
		rectSourceSprite.top = row * rectSourceSprite.height;
		m_sprite.setTextureRect(rectSourceSprite);
	}
}
void Fish::move()
{
	fishHB = new Rectangle(m_sprite.getPosition().x - 20, m_sprite.getPosition().y - 12, 32, 32);
	m_box.setPosition(m_sprite.getPosition().x - 20, m_sprite.getPosition().y - 12);
	m_sprite.move(-speed, 0);


	light.followCentre(sf::Vector2f(m_sprite.getPosition().x+10, m_sprite.getPosition().y+8));
	light.scale(0.15, 0.15);
	
}
void Fish::render(sf::RenderWindow & t_window)
{
	//t_window.draw(m_box);
	t_window.draw(light.draw());
	t_window.draw(m_sprite);
	for (int i = 0; i < currTxt; i++)
	{
		t_window.draw(m_text[i]);
	}
}

void Fish::boundary()
{
	{
		if (m_sprite.getPosition().x < -50)
		{
			m_sprite.setPosition(rand() % 300 + (WINDOW_WIDTH + 200), rand() % (WINDOW_HEIGHT - 150) + 100);
		}
	}
}

void Fish::animateDeath()
{
}

void Fish::setText()
{
	if (currTxt >= 3)
	{
		currTxt = 0;
	}
	m_text[currTxt].setPosition(m_sprite.getPosition());

	currTxt++;
	
}

void Fish::moveText()
{
	for (int i = 0; i < 3; i++)
	{
		if (m_text[i].getPosition().y > -400)
		{
			m_text[i].move(-2.4, -3.4);
		}
	}
	
}


