#ifndef DAMAGED_PLAYER_STATE_H
#define DAMAGED_PLAYER_STATE_H
#include "Player.h"
#include "PlayerState.h"

class DamagedPlayerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);

private:
	sf::Clock m_clock;
};
#endif