
#pragma once

#include "iinput.h"

class InputNetwork : public IInput
{

	public:
		virtual void EventOccurred(Event* e);
		virtual int GetPlayerInput();

};