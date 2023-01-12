#pragma once
#include"Enemy.h"
class Mine : public Enemy
{
private:
	float speed = 3;
	float idleSpeed = 0.15;
	sf::Texture m_texture;
	sf::Texture m_explodingTexture;
	sf::Sprite m_sprite;
	sf::RectangleShape m_box{ sf::Vector2f(95,95) };
	Rectangle* mineHB;
	bool damaged = false;
	int mineTimer = 0;
	int explosionTimer = 0;
	int explosionFrame = 0;
public:
	virtual void update();
	virtual void loadTextures();
	virtual void animate();
	virtual void move();
	virtual void render(sf::RenderWindow& t_window);
	virtual void boundary();
	virtual Rectangle* CollisionBox() { return mineHB; };
	virtual sf::Sprite getBody() { return m_sprite; };

	virtual void animateDeath();
	virtual void setDamageF() {damaged = false;}
	virtual void setDamageT()
	{
		m_sprite.setTexture(m_explodingTexture);;
		damaged = true;
	}

	
};

