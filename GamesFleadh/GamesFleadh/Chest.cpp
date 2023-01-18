#include "Chest.h"

void Chest::render(sf::RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(pearls[i].draw());
		//window.draw(pearls[i].drawBox());
	}
	
	window.draw(m_chest);

}

void Chest::update()
{
	for (int i = 0; i < 3; i++)
	{
		pearls[i].move();
		pearls[i].setHBPos();
	}
	move();
	timePearls();

}

void Chest::initialise()
{
	if (!m_chestTexture.loadFromFile(CHESTS))
	{
		std::cout << "error loading chests";
	}

	m_chest.setTexture(m_chestTexture);
	m_chest.setTextureRect(sf::IntRect(0, 0, 48, 32));
	m_chest.setPosition(sf::Vector2f((rand() % 800) + 1700, 790));
	m_chest.setScale(3, 3);
}

void Chest::setPosition()
{
	m_chest.setPosition(sf::Vector2f((rand() % 800) + 1700, 790));
	chestSpawn = false;
	m_chest.setTextureRect(sf::IntRect(0, 0, 48, 32));
	chestFrame = 0;
}

void Chest::timePearls()
{
	if (!chestSpawn)
	{
		if (m_chest.getPosition().x < 1350)
		{
			if (chestSpawnTimer == 0)
			{
				chestSpawnTimer = rand() % 200 + 100;
			}
			chestSpawnTimer--;
			if (chestSpawnTimer <= 0)
			{
				spawnedPearls = false;
				chestSpawn = true;
				chestTimer = 0;
			}
		}
	}
	else
	{
		animate();
	}
}

void Chest::updateHB()
{
}

void Chest::move()
{
	m_chest.move(-2.4, 0);
}

void Chest::animate()
{
	chestTimer++;
	if (chestTimer > 10)
	{
		chestFrame++;
		if (chestFrame > 9) //frame 44 is the last frame the robot is running
		{
			chestFrame = 9; //37 is the first frame the robot is running
			if (!spawnedPearls)
			{
				for (int i = 0; i < 3; i++)
				{
					pearls[i].pearlSetToChest(m_chest.getPosition());
				}
				spawnedPearls = true;
			}

		}
		chestTimer = 0;
	}
	int col = chestFrame % 5; //total cols is 5
	int row = chestFrame / 5; //

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 32;
	rectSourceSprite.width = 48;
	rectSourceSprite.left = col * rectSourceSprite.width;
	rectSourceSprite.top = row * rectSourceSprite.height;
	m_chest.setTextureRect(rectSourceSprite);
}

void Chest::checkCollision(Player* t_player)
{
	for (int i = 0; i < 3; i++)
	{
		if (t_player->CollisionBox()->checkRectangleCollision(pearls[i].collisionBox()))
		{
			pearls[i].PearlSetPos();
			t_player->addPearls();
		}
	}
}

