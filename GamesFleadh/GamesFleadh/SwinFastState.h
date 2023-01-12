#ifndef SWIN_FAST_STATE_H
#define SWIM_FAST_PLAYER_STATE_H

#include "Player.h"
#include "PlayerState.h"

class SwimFastState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);
};

#endif

