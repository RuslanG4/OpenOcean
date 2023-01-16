#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include"Defines.h"
#include"Collision.h"

class Plant
{
private:
	sf::Sprite m_bubble;
	sf::Texture m_texture;

	sf::Sprite m_plant;
	sf::Texture m_plantTexture;

	sf::RectangleShape m_box{ sf::Vector2f(64,64) };
	Rectangle* pearlHB;

	sf::Vector2f offScreenPos{-400, -400};

	int bubbleTimer = 0;
	int bubbleFrame = 0;

	int bubbleSpawnTimer = 0;
	bool bubbleSpawn = false;

public:
	void render(sf::RenderWindow& window);
	void update();
	void initialise();
	void setPosition() { m_plant.setPosition(sf::Vector2f((rand() % 800) + 1500, 780)); bubbleSpawn = false; };
	void bubbleSetPos() { m_bubble.setPosition(offScreenPos); };
	void timeBubbles();
	void updateHB();
	sf::Vector2f getPosition() { return m_bubble.getPosition(); };
	void move();
	Rectangle* CollisionBox() { return pearlHB; };
	void animate();
	sf::Vector2f plantPos() { return m_plant.getPosition(); };
};

