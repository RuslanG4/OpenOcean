#include "Events.h"

#include "RunRightPlayerState.h"
#include "IdlePlayerState.h"
#include"DamagedPlayerState.h"
#include"SwinFastState.h"



PlayerState* RunRightPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::SWIM_FAST)
	{
		DEBUG_MSG("RunRightPlayerState -> SwimFastPlayerState");
		return new SwimFastState();
	}
	if (input.getCurrent() == gpp::Events::Event::SWIM_RIGHT_STOP_EVENT)
	{
		DEBUG_MSG("RunRightPlayerState -> IdlePlayerState");
		return new IdlePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DAMAGE_TAKEN)
	{
		DEBUG_MSG("RunRightPlayerState -> DamagedPlayerState");
		return new DamagedPlayerState();
	}
	return nullptr;
}
void RunRightPlayerState::update(Player& player) {}
void RunRightPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering RunRightPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 320, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(80, 320, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(160, 320, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(240, 320, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(320, 320, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(401, 320, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(480, 320, 80, 82));

	player.getAnimatedSpriteFrame().setTime(seconds(0.15f));
}
void RunRightPlayerState::exit(Player& player) 
{
	DEBUG_MSG("Exiting RunRightPlayerState");
}