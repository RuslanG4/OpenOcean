#include "Events.h"

#include "IdlePlayerState.h"
#include "RunRightPlayerState.h"
#include"DamagedPlayerState.h"




PlayerState* IdlePlayerState::handleInput(gpp::Events& input) {

	if (input.getCurrent() == gpp::Events::Event::SWIM_RIGHT_START_EVENT) {
		DEBUG_MSG("IdlePlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	if (input.getCurrent() == gpp::Events::Event::DAMAGE_TAKEN)
	{
		DEBUG_MSG("RunRightPlayerState -> IdlePlayerState");
		return new DamagedPlayerState();
	}

	return nullptr;
}

void IdlePlayerState::update(Player& player) {}

void IdlePlayerState::enter(Player& player) 
{
	DEBUG_MSG("Entering IdlePlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 164, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(80, 164, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(160, 164, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(240, 164, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(320, 164, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(400, 164, 80, 82));

	
	player.getAnimatedSprite().setTime(seconds(0.15f));
}

void IdlePlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting IdlePlayerState");
}