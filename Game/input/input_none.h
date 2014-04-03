
#pragma once

#include "iinput.h"

class InputNone : public IInput
{

	public:
		virtual void EventOccurred(Event* e);
		virtual int GetPlayerInput();

};