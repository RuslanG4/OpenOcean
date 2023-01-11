#include"Events.h"

#include "DamagedPlayerState.h"
#include "IdlePlayerState.h"
#include "RunRightPlayerState.h"

PlayerState* DamagedPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::SWIM_RIGHT_START_EVENT)
	{
		return new IdlePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DAMAGE_TAKEN_STOP)
	{
		return new IdlePlayerState();
	}
    return nullptr;
}

void DamagedPlayerState::update(Player& player)
{
	if (m_clock.getElapsedTime().asSeconds() > 0.7f) {
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new IdlePlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
}

void DamagedPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering RunRightPlayerState");

	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 82, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(80, 82, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(160, 82, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(240, 82, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(320, 82, 80, 82));


	player.getAnimatedSpriteFrame().setTime(seconds(0.12f));
}

void DamagedPlayerState::exit(Player& player)
{

}
