#include "SwinFastState.h"
#include "Events.h"

#include "RunRightPlayerState.h"
#include "IdlePlayerState.h"
#include	"DamagedPlayerState.h"



PlayerState* SwimFastState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::SWIM_RIGHT_START_EVENT)
	{
		DEBUG_MSG("SwimFastPlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	if (input.getCurrent() == gpp::Events::Event::DAMAGE_TAKEN)
	{
		DEBUG_MSG("SwimFastPlayerState -> DamgedPlayerState");
		return new DamagedPlayerState();
	}
	return nullptr;
}
void SwimFastState::update(Player& player) {}
void SwimFastState::enter(Player& player)
{
	DEBUG_MSG("Entering SwimFastPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 240, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(80, 240, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(160, 240, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(240, 240, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(320, 240, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(401, 240, 80, 82));
	player.getAnimatedSprite().addFrame(sf::IntRect(480, 240, 80, 82));

	player.getAnimatedSpriteFrame().setTime(seconds(0.10f));
}
void SwimFastState::exit(Player& player)
{
	DEBUG_MSG("Exiting SwimFastPlayerState");
}
