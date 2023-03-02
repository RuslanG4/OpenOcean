#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Defines.h"
#include"Collision.h"
#include"Light.h"
#include<SFML/Audio.hpp>

class Shell
{
private:
	Light light;


	sf::Sprite m_shell;
	sf::Texture m_shellTexture;

	sf::RectangleShape m_box{ sf::Vector2f(42,30) };
	Rectangle* shellHB;

	sf::Vector2f offScreenPos{ -400, -400 };

	sf::Text m_text;
	sf::Font font;

	bool startMove = false;

	sf::Music shellSound;

	bool sound = false;

	int rotation = 0;

	sf::Music pop;



public:
	Shell();

	void init();
	void render(sf::RenderWindow& window);
	void update();

	void updateHB();
	sf::Vector2f getPosition() { return m_shell.getPosition(); };

	void move();

	Rectangle* CollisionBox() { return shellHB; };

	void setText();
	void moveText();

	void respawn();

	void soundPlay();

};



