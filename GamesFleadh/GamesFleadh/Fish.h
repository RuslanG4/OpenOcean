#pragma once
#include"Enemy.h"
class Fish : public Enemy
{
private:
	float speed = 6;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::RectangleShape m_box{ sf::Vector2f(32,32) };
	Rectangle* fishHB;
	bool damaged = false;
	int fishTimer = 0;
	int fishFrame = 0;

	Light light;

	sf::Text m_text[3];
	sf::Font font;

	int currTxt=0;

	bool startMove = false;

public:
	virtual void update(sf::Vector2f t_playerPos);
	virtual void loadTextures();
	virtual void animate();
	virtual void move();
	virtual void render(sf::RenderWindow& t_window);
	virtual void boundary();
	virtual Rectangle* CollisionBox() { return fishHB; };
	virtual sf::Sprite getBody() { return m_sprite; };
	virtual void animateDeath();
	virtual void setDamageF() { damaged = false; }
	virtual void setDamageT() { damaged = true; }
	virtual void aiBehaviour() {};
	virtual bool isChasing() { return 1; };
	void sound() {};

	void setText() ;
	void moveText() ;
};

