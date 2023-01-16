#include "Mine.h"
void Mine::update(sf::Vector2f t_playerPos)
{
	animate();
	move();
	boundary();
	if (damaged)
	{
		animateDeath();
	}
}
void Mine::loadTextures()
{
	if (!m_texture.loadFromFile(MINE_BIG))
	{
		std::cout << "error loading fish";
	}
	if (!m_explodingTexture.loadFromFile(MINE_BIG_EXPLOSION))
	{
		std::cout << "error loading big explosion";
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setColor(sf::Color::Yellow);
	m_sprite.setScale(2, 2);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 85, 85));
	m_sprite.setPosition(rand() % 400 + 1600, rand() % 650 + 100);

	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(3);
}
void Mine::render(sf::RenderWindow& t_window)
{
	//t_window.draw(m_box);
	t_window.draw(m_sprite);
}
void Mine::animate()
{
	mineTimer++;
	if (mineTimer < 40)
	{
		m_sprite.move(0, -idleSpeed);
	}
	if (mineTimer > 40)
	{
		m_sprite.move(0, idleSpeed);
	}
	if (mineTimer > 80)
	{
		mineTimer = 0;
	}
	
}
void Mine::move()
{
	mineHB = new Rectangle(m_sprite.getPosition().x+35, m_sprite.getPosition().y+35, 95, 95);
	m_box.setPosition(m_sprite.getPosition().x + 35, m_sprite.getPosition().y+35);
	m_sprite.move(-speed, 0);
}
void Mine::boundary()
{
	if (m_sprite.getPosition().x < -150)
	{
		m_sprite.setPosition(rand() % 300 + 1600, rand() % 650 + 100);
		m_sprite.setTexture(m_texture);
		damaged = false;
	}
}

void Mine::animateDeath()
{
	explosionTimer++;
	if (explosionTimer > 3)
	{
		explosionFrame++;
		if (explosionFrame >= 10) //frame 44 is the last frame the robot is running
		{
			explosionFrame = 0; //37 is the first frame the robot is running
			damaged = false;
			m_sprite.setPosition(rand() % 300 + 1600, rand() % 650 + 100);
			m_sprite.setTexture(m_texture);
		}
		explosionTimer = 0;
	}
	int col = explosionFrame % 10; //total cols is 5
	int row = 0; //

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 85;
	rectSourceSprite.width = 85;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	m_sprite.setTextureRect(rectSourceSprite);


}


