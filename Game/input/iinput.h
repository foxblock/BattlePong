
#pragma once

#include "../../Framework/event.h"

#define PLAYER_CONTROLS_NONE	0
#define PLAYER_CONTROLS_UP		1
#define PLAYER_CONTROLS_DOWN	2
#define PLAYER_CONTROLS_SEND	4
#define PLAYER_CONTROLS_USEA	8
#define PLAYER_CONTROLS_USEB	16
#define PLAYER_CONTROLS_USEC	32

class IInput
{

	public:
		virtual void EventOccurred(Event* e) = 0;
		virtual int GetPlayerInput() = 0;

};