
#pragma once

#include "iinput.h"

class InputAIEasy : public IInput
{

	public:
		virtual void EventOccurred(Event* e);
		virtual int GetPlayerInput();

};