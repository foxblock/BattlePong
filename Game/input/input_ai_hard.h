
#pragma once

#include "iinput.h"

class InputAIHard : public IInput
{

	public:
		virtual void EventOccurred(Event* e);
		virtual int GetPlayerInput();

};