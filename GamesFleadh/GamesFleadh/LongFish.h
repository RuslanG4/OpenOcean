#pragma once
#include"Enemy.h"
class LongFish : public Enemy
{
private:
	float speed = 10;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::RectangleShape m_box{ sf::Vector2f(40,20) };
	bool damaged = false;
	Rectangle* fishHB;
	int fishTimer = 0;
	int fishFrame = 0;
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
};

