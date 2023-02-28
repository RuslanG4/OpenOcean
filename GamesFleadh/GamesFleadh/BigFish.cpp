#include "BigFish.h"

void BigFish::update(sf::Vector2f t_playerPos)
{
	fishHB = new Rectangle(m_sprite.getPosition().x - 36, m_sprite.getPosition().y - 16, 54, 49);
	m_box.setPosition(m_sprite.getPosition().x - 36, m_sprite.getPosition().y - 16);

	animate();
	if (!chase)
	{
		move();
	}
	boundary();
	aiBehaviour();
	chaseAI(t_playerPos);
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
	m_sprite.setPosition(rand() % 300 + (WINDOW_WIDTH + 200), rand() % (WINDOW_HEIGHT - 150) + 100);

	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(3);

	light = Light{ sf::Vector2f(500,300) };
	light.setMaxLight(255);
	light.setIntensity(0.6);
	light.selectColour(sf::Color(0, 0, 0), sf::Color(128, 128, 128));
}
void BigFish::render(sf::RenderWindow& t_window)
{
	//t_window.draw(m_box);
	t_window.draw(light.draw());
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

	light.followCentre(sf::Vector2f(m_sprite.getPosition().x+5, m_sprite.getPosition().y+20));
	light.scale(0.25, 0.25);
}
void BigFish::boundary()
{
	if (hasChased)
	{
		if (m_sprite.getPosition().x < -60)
		{
			m_sprite.setPosition(rand() % 300 + (WINDOW_WIDTH+200), rand() % (WINDOW_HEIGHT-150) + 100);
			hasChased = false;
			chase = false;
		}
	}
	if (chase && !hasChased )
	{
		if (m_sprite.getPosition().x >20)
		{
			m_sprite.setPosition(20,m_sprite.getPosition().y);
			light.followCentre(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y + 20));
			light.scale(0.25, 0.25);
		}
	}
}

void BigFish::animateDeath()
{
}

void BigFish::aiBehaviour()
{
	if (m_sprite.getPosition().x <  -100 && !hasChased)
	{
		chase = true;
	}
}

void BigFish::chaseAI(sf::Vector2f t_playerPos)
{
	position = m_sprite.getPosition();
	if (chase)
	{
		m_sprite.setScale(2, 2);
		chaseDirection = t_playerPos - m_sprite.getPosition();
		thor::setLength(chaseDirection, float(2));
		position += chaseDirection;
		m_sprite.setPosition(position);
		if (position.y < t_playerPos.y)
		{
			m_sprite.setRotation(15);
		}
		else
		{
			m_sprite.setRotation(-15);
		}
		 
		chaseTimer++;
		if (chaseTimer > 540)
		{
			m_sprite.setRotation(0);
			m_sprite.setScale(-2, 2);
			chase = false;
			hasChased = true;
			chaseTimer = 0;
		
			
		}
	}
	
}


