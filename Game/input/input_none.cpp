
#include "input_none.h"

void InputNone::EventOccurred( Event* e )
{
}

int InputNone::GetPlayerInput()
{
	return PLAYER_CONTROLS_NONE;
}