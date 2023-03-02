#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Defines.h"
#include"Collision.h"
#include"Light.h"

class Plant
{
private:
	Light plantLight;
	Light bubbleLight;

	sf::Sprite m_bubble;
	sf::Texture m_texture;

	sf::Sprite m_plant;
	sf::Texture m_plantTexture;

	sf::RectangleShape m_box{ sf::Vector2f(64,64) };
	Rectangle* pearlHB;

	sf::Vector2f offScreenPos{-400, -400};

	sf::Text m_text;
	sf::Font font;

	bool startMove = false;

	int bubbleTimer = 0;
	int bubbleFrame = 0;

	int bubbleSpawnTimer = 0;
	bool bubbleSpawn = false;


	sf::Music bubbleSound;
	bool sound = false;
	

public:
	void render(sf::RenderWindow& window);
	void update();
	void initialise();
	void setPosition();
	void bubbleSetPos() { m_bubble.setPosition(offScreenPos); };
	void timeBubbles();
	void updateHB();
	sf::Vector2f getPosition() { return m_bubble.getPosition(); };
	void move();
	Rectangle* CollisionBox() { return pearlHB; };
	void animate();
	sf::Vector2f plantPos() { return m_plant.getPosition(); };

	void playBubble();

	void setText();
	void moveText();

};

