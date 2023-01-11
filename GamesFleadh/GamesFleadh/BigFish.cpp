#include "BigFish.h"

void BigFish::update()
{
	animate();
	move();
	boundary();
}
void BigFish::loadTextures()
{
	if (!m_texture.loadFromFile(BIG_FISH_SPRITES))
	{
		std::cout << "error loading fish";
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(-2, 2);
	m_sprite.setOrigin(27, 24);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 54, 49));
	m_sprite.setPosition(rand() % 300 + 1600, rand() % 800 + 100);

	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(3);
}
void BigFish::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_box);
	t_window.draw(m_sprite);
}
void BigFish::animate()
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
	rectSourceSprite.height = 49;
	rectSourceSprite.width = 54;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	m_sprite.setTextureRect(rectSourceSprite);
}
void BigFish::move()
{
	fishHB = new Rectangle(m_sprite.getPosition().x - 36, m_sprite.getPosition().y - 16, 54, 49);
	m_box.setPosition(m_sprite.getPosition().x - 36, m_sprite.getPosition().y - 16);
	m_sprite.move(-speed, 0);
}
void BigFish::boundary()
{
	if (m_sprite.getPosition().x < -50)
	{
		m_sprite.setPosition(rand() % 300 + 1600, rand() % 800 + 100);
	}
}


