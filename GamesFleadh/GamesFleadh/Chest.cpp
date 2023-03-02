#include "Chest.h"

void Chest::render(sf::RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(pearls[i].drawLight());
		window.draw(pearls[i].draw());
		//window.draw(pearls[i].drawBox());
		window.draw(pearls[i].drawText());
	}
	window.draw(chestLight.draw());
	window.draw(m_chest);

	

}

void Chest::update()
{
	for (int i = 0; i < 3; i++)
	{
		pearls[i].move();
		pearls[i].setHBPos();

		if (pearls[i].getTextSpawn())
		{
			pearls[i].moveText();
		}

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
	m_chest.setPosition(sf::Vector2f((rand() % 800) + (WINDOW_WIDTH +500), (WINDOW_HEIGHT - 160)));
	m_chest.setScale(3, 3);

	chestLight = Light{ sf::Vector2f(m_chest.getPosition().x + 40, m_chest.getPosition().y + 60) };
	chestLight.scale(0.75, 0.75);
	chestLight.setMaxLight(255);
}

void Chest::setPosition()
{
	m_chest.setPosition(sf::Vector2f((rand() % 800) + (WINDOW_WIDTH + 500), (WINDOW_HEIGHT - 160)));
	chestSpawn = false;
	m_chest.setTextureRect(sf::IntRect(0, 0, 48, 32));
	chestFrame = 0;
	chestLight = Light{ sf::Vector2f(m_chest.getPosition().x + 40,m_chest.getPosition().y + 60) };
	chestLight.scale(0.75, 0.75);
}

void Chest::timePearls()
{
	if (!chestSpawn)
	{
		if (m_chest.getPosition().x < 1750)
		{
			if (chestSpawnTimer == 0)
			{
				chestSpawnTimer = rand() % 100 + 100;
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
	m_chest.move(-3.6, 0);
	chestLight.moveLight(-3.6, 0);
}

void Chest::animate()
{
	chestTimer++;
	if (chestTimer > 10)
	{
		chestFrame++;
		if (chestFrame == 4)
		{
			playChest();
		}
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
			pearls[i].setText();
			pearls[i].PearlSetPos();
			pearls[i].playSound();
			t_player->addPearls();
			t_player->updateScore(75);
		}
	}
}

void Chest::playChest()
{
	if (!chestSound.openFromFile("ASSETS\\AUDIO\\chest.wav"))
	{
		std::cout << "error laoding music";
	}
	chestSound.setVolume(30);
	chestSound.play();
}

void Pearl::playSound()
{
	if (!itemSound.openFromFile("ASSETS\\AUDIO\\shellPickUp.wav"))
	{
		std::cout << "error laoding music";
	}

	itemSound.setVolume(30);
	itemSound.play();
}

void Pearl::setText()
{
	startMove = true;
	m_text.setPosition(m_pearl.getPosition());
}

void Pearl::moveText()
{
	m_text.move(-2.4, -3.4);


	if (m_text.getPosition().y < -50)
	{
		m_text.setPosition(1300, 1080);
		startMove = false;
	}
}
