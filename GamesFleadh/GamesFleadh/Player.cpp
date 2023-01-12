#include <stdio.h>
#include "Player.h"
#include "Events.h"
#include "IdlePlayerState.h"


Player::Player(const AnimatedSprite& sprite) : m_animated_sprite(sprite)
{
	// Set the Player to Default to IdlePlayer State 
	// and Enter that State
	m_state = new IdlePlayerState();
	m_state->enter(*this);
	m_animated_sprite.setOrigin(40, 42);
	m_animated_sprite.setPosition(200,200);
	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(3);
}

void Player::handleInput(gpp::Events input) {
	PlayerState * state = m_state->handleInput(input);

	if (state != NULL) {
		m_state->exit(*this);
		delete m_state;
		m_state = state;
		m_state->enter(*this);
	}
}

void Player::update() {
	m_animated_sprite.update();
	m_state->update(*this);

	move();
	boundary();
	HB();
}

AnimatedSprite& Player::getAnimatedSprite() {
	return m_animated_sprite;
}

AnimatedSprite& Player::getAnimatedSpriteFrame() {
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	return m_animated_sprite;
}

void Player::setAnimatedSprite(AnimatedSprite& animated_sprite) {
	this->m_animated_sprite = animated_sprite;
}

PlayerState* Player::getPlayerState() { return this->m_state; }

void Player::setPlayerState(PlayerState* state) { this->m_state = state; }

void Player::render(sf::RenderWindow& window)
{
	//window.draw(m_box);
}

float Player::vectorLengthSquared()
{
	const float length = (m_veloctiy.x * m_veloctiy.x) + (m_veloctiy.y * m_veloctiy.y);
	return length;
}

void Player::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_veloctiy.x=2;
		m_animated_sprite.setScale(2, 2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_veloctiy.x = -2;
		m_animated_sprite.setScale(-2, 2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_veloctiy.y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_veloctiy.y = 1;
	}

	m_veloctiy = m_veloctiy * FRICTION;
	m_position += m_veloctiy;
	m_animated_sprite.setPosition(m_position);
}

void Player::boundary()
{
	if (m_position.x > 700)
	{
		m_position.x = 700;
	}
}

void Player::HB()
{
	if (isMoving)
	{
		playerHB = new Rectangle(m_animated_sprite.getPosition().x - 40, m_animated_sprite.getPosition().y, 80, 30);
		m_box.setSize(sf::Vector2f(80, 30));
		m_box.setPosition(m_animated_sprite.getPosition().x - 40, m_animated_sprite.getPosition().y);
	}
	else
	{
		playerHB = new Rectangle(m_animated_sprite.getPosition().x - 10, m_animated_sprite.getPosition().y - 40, 40, 80);
		m_box.setSize(sf::Vector2f(40, 80));
		m_box.setPosition(m_animated_sprite.getPosition().x - 10, m_animated_sprite.getPosition().y - 40);
	}
}



