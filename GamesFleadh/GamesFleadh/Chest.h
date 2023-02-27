#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Defines.h"
#include"Collision.h"
#include"Player.h"
#include"Light.h"

class Pearl
{
private:
	Light pearlLight;

	sf::Sprite m_pearl;
	sf::Texture m_pearlsTexture;

	sf::RectangleShape m_box{ sf::Vector2f(8,8) };
	Rectangle* pearlHB;

	sf::Vector2f offScreenPos{ -400, -400 };

	sf::Music itemSound;

public:
	Pearl()
	{
		if (!m_pearlsTexture.loadFromFile(PEARL))
		{
			std::cout << "error loading chests";
		}
		m_pearl.setTexture(m_pearlsTexture);
		m_pearl.setScale(0.25, 0.25);
		m_pearl.setPosition(offScreenPos);

		m_box.setOutlineThickness(3);
		m_box.setFillColor(sf::Color::Transparent);

		pearlLight = Light{ m_pearl.getPosition() };
		pearlLight.setMaxLight(255);
	};
	void PearlSetPos() { m_pearl.setPosition(offScreenPos); };
	void pearlSetToChest(sf::Vector2f t_position)
	{
		m_pearl.setPosition(t_position.x + rand()% 75 + 5, t_position.y + 60 +rand()%50);
		pearlLight.followCentre(sf::Vector2f(m_pearl.getPosition().x + 10, m_pearl.getPosition().y + 10));
		pearlLight.scale(0.1, 0.1);
	};
	void move()
	{
		m_pearl.move(-1.5, -2);
		pearlLight.followCentre(sf::Vector2f(m_pearl.getPosition().x+5,m_pearl.getPosition().y+5));
		pearlLight.scale(0.1, 0.1);
	};
	void setHBPos() { m_box.setPosition(m_pearl.getPosition()); pearlHB = new Rectangle(m_pearl.getPosition().x, m_pearl.getPosition().y, 8, 8); }
	sf::Vector2f getPosition() { return m_pearl.getPosition(); };
	sf::Sprite draw() { return m_pearl; };
	sf::VertexArray drawLight() { return pearlLight.draw(); }
	sf::RectangleShape drawBox() { return m_box; };
	Rectangle* collisionBox() { return pearlHB; };
	void playSound();
};

class Chest
{
private:
	Light chestLight;

	Pearl pearls[3];

	sf::Sprite m_chest;
	sf::Texture m_chestTexture;

	int chestTimer = 0;
	int chestFrame = 0;

	int chestSpawnTimer = 0;
	bool chestSpawn = false;

	bool spawnedPearls = false;

	sf::Music chestSound;
	
public:
	void render(sf::RenderWindow& window);
	void update();
	void initialise();
	void setPosition();
	void timePearls();
	void updateHB();
	void move();
	void animate();
	sf::Vector2f chestPos() { return m_chest.getPosition(); };
	void checkCollision(Player* t_player);
	void playChest();

};

