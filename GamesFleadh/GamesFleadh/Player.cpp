#include <stdio.h>
#include "Player.h"
#include "Events.h"
#include "IdlePlayerState.h"
#include"RunRightPlayerState.h"


Player::Player(const AnimatedSprite& sprite) : m_animated_sprite(sprite)
{

	//Set the Player to Default to IdlePlayer State 
	// and Enter that State
	m_state = new RunRightPlayerState();
	m_state->enter(*this);
	m_animated_sprite.setOrigin(40, 42);
	m_animated_sprite.setPosition(200, 200);
	m_animated_sprite.setScale(3.5, 3.5);
	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(3);
	playerHB = new Rectangle(m_animated_sprite.getPosition().x - 20, m_animated_sprite.getPosition().y + 5, 100, 25);
	m_box.setSize(sf::Vector2f(100, 25));
	m_box.setPosition(m_animated_sprite.getPosition().x - 20, m_animated_sprite.getPosition().y + 5);

	playerLight = Light{ m_animated_sprite.getPosition() };

	playerLight.setMaxLight(104);
	playerLight.setIntensity(0.6);
	
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

	m_veloctiy.x = -pushbackSpeed;
	m_veloctiy = m_veloctiy * FRICTION;
	m_position += m_veloctiy;
	m_animated_sprite.setPosition(m_position);
	//move();

	boundary();
	HB();
	updateOxy();

	playerLight.followCentre(sf::Vector2f(m_animated_sprite.getPosition().x+50, m_animated_sprite.getPosition().y));
	playerLight.scale(0.7, 0.7);
	
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
	window.draw(playerLight.draw());
}

void Player::boundary()
{
	if (m_position.x > 750)
	{
		m_position.x = 750;
	}
	if (m_position.y < 20)
	{
		m_position.y = 20;
	}
	if (m_position.y > WINDOW_HEIGHT-50)
	{
		m_position.y = WINDOW_HEIGHT - 50;
	}
	if (m_position.x < -70)
	{
		isAlive = false;
	}
}

void Player::moveLEAP(std::string t_action)
{
	if (t_action == "right-hand")
	{
		m_veloctiy.x = 1.15;
		m_animated_sprite.setScale(3.5, 3.5);
	}
	else if (t_action == "left-hand")
	{
		m_veloctiy.x = 1.15;
		m_animated_sprite.setScale(3.5, 3.5);
	}
	if (t_action == "fingers")
	{
		m_veloctiy.y = -0.9;
	}
	else if (t_action == "fingersDown")
	{
		m_veloctiy.y = 0.9;
	}
	m_position += m_veloctiy;
	m_animated_sprite.setPosition(m_position);
}

void Player::HB()
{
	playerHB = new Rectangle(m_animated_sprite.getPosition().x - 20, m_animated_sprite.getPosition().y+5, 100, 35);
	m_box.setSize(sf::Vector2f(100, 35));
	m_box.setPosition(m_animated_sprite.getPosition().x - 20, m_animated_sprite.getPosition().y + 5);
}

void Player::hit()
{ 
	oxygenLvl -= 5;
	if (oxygenLvl <= 0)
	{
		oxygenLvl = 0;
	}
	pushbackSpeed = 4;
}

void Player::updateOxy()
{
	if (m_oxyTimer.getElapsedTime().asSeconds() > 1)
	{
		oxygenLvl--;
		if (oxygenLvl <= 0)
		{
			isAlive = false;
			oxygenLvl = 0;
		}
		m_oxyTimer.restart();
	}
}



