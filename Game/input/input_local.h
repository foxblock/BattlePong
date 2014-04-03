
#pragma once

#include "iinput.h"

class InputLocal : public IInput
{

	private:
		int KeyState;

		int UpKey;
		int DownKey;
		int SendKey;
		int UseAKey;
		int UseBKey;
		int UseCKey;

	public:
		InputLocal(int PlayerNumber, bool IsSinglePlayer);
		virtual void EventOccurred(Event* e);
		virtual int GetPlayerInput();

};