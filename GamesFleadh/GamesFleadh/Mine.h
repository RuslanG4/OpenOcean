#pragma once
#include"Enemy.h"
class Mine : public Enemy
{
private:
	sf::Music mineSound;

	Light mineLight;

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

	bool soundPlayed = false;

	sf::Text m_text;
	sf::Font font;

	bool startMove = false;

public:
	virtual void update(sf::Vector2f t_playerPos);
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
	virtual void aiBehaviour() {};
	virtual bool isChasing() { return 1; };

	void sound();

	void setText() ;
	void moveText();

	
};

