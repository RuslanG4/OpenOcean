#pragma once
#include <SFML/Graphics.hpp>
#include"Defines.h"
#include"Collision.h"
#include<iostream>
#include"Thor/Vectors.hpp"


class Enemy
{
private:
public:
	virtual void loadTextures() =0;
	virtual void animate() = 0;
	virtual void render(sf::RenderWindow& t_window) = 0;
	virtual void update(sf::Vector2f t_playerPos)=0;
	virtual void move() = 0;
	virtual void boundary() = 0;
	virtual Rectangle* CollisionBox() = 0;
	virtual sf::Sprite getBody()=0;
	virtual void animateDeath() = 0;
	virtual void setDamageF() = 0;
	virtual void setDamageT() = 0;
	virtual void aiBehaviour() = 0;
	virtual bool isChasing() { return 1; };

};



