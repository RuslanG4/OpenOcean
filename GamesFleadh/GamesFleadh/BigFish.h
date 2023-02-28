#pragma once
#include"Enemy.h"
class BigFish : public Enemy
{
private:

	Light light;

	float speed = 2;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::RectangleShape m_box{ sf::Vector2f(54,49) };
	Rectangle* fishHB;

	sf::Vector2f position;
	bool damaged = false;
	int fishTimer = 0;
	int fishFrame = 0;

	bool chase = false;
	bool hasChased = false;

	int chaseTimer = 0;

	sf::Vector2f chaseDirection;

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
	void aiBehaviour();
	void chaseAI(sf::Vector2f t_playerPos);
	virtual bool isChasing() { return chase; };
	void sound() {};
};

