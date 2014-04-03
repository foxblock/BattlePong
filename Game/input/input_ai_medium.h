
#pragma once

#include "iinput.h"

class InputAIMedium : public IInput
{

	public:
		virtual void EventOccurred(Event* e);
		virtual int GetPlayerInput();

};