
#include "input_local.h"

InputLocal::InputLocal( int PlayerNumber, bool IsSinglePlayer )
{
	KeyState = 0;

	if( IsSinglePlayer )
	{
		UpKey = SDLK_UP;
		DownKey = SDLK_DOWN;
		SendKey = SDLK_PAGEUP;
		UseAKey = SDLK_HOME;
		UseBKey = SDLK_PAGEDOWN;
		UseCKey = SDLK_END;
	} else {
		switch( PlayerNumber )
		{
			case 1:
				UpKey = SDLK_UP;
				DownKey = SDLK_DOWN;
				SendKey = SDLK_RIGHT;
				UseAKey = SDLK_q;
				UseBKey = SDLK_a;
				UseCKey = SDLK_z;
				break;
			case 2:
				UpKey = SDLK_PAGEUP;
				DownKey = SDLK_PAGEDOWN;
				SendKey = SDLK_HOME;
				UseAKey = SDLK_o;
				UseBKey = SDLK_k;
				UseCKey = SDLK_m;
				break;
		}
	}

}

void InputLocal::EventOccurred( Event* e )
{
	if( e->Type == EVENT_KEY_DOWN )
	{

		// Toggle key flags
		if( e->Data.Keyboard.keysym.sym == UpKey )
		{
			KeyState = KeyState | PLAYER_CONTROLS_UP;
		}
		if( e->Data.Keyboard.keysym.sym == DownKey )
		{
			KeyState = KeyState | PLAYER_CONTROLS_DOWN;
		}
		if( e->Data.Keyboard.keysym.sym == SendKey )
		{
			KeyState = KeyState | PLAYER_CONTROLS_SEND;
		}
		if( e->Data.Keyboard.keysym.sym == UseAKey )
		{
			KeyState = KeyState | PLAYER_CONTROLS_USEA;
		}
		if( e->Data.Keyboard.keysym.sym == UseBKey )
		{
			KeyState = KeyState | PLAYER_CONTROLS_USEB;
		}
		if( e->Data.Keyboard.keysym.sym == UseCKey )
		{
			KeyState = KeyState | PLAYER_CONTROLS_USEC;
		}

	} else if ( e->Type == EVENT_KEY_UP ) {

		// Toggle key flags
		if( e->Data.Keyboard.keysym.sym == UpKey )
		{
			KeyState = KeyState & ~PLAYER_CONTROLS_UP;
		}
		if( e->Data.Keyboard.keysym.sym == DownKey )
		{
			KeyState = KeyState & ~PLAYER_CONTROLS_DOWN;
		}
		if( e->Data.Keyboard.keysym.sym == SendKey )
		{
			KeyState = KeyState & ~PLAYER_CONTROLS_SEND;
		}
		if( e->Data.Keyboard.keysym.sym == UseAKey )
		{
			KeyState = KeyState & ~PLAYER_CONTROLS_USEA;
		}
		if( e->Data.Keyboard.keysym.sym == UseBKey )
		{
			KeyState = KeyState & ~PLAYER_CONTROLS_USEB;
		}
		if( e->Data.Keyboard.keysym.sym == UseCKey )
		{
			KeyState = KeyState & ~PLAYER_CONTROLS_USEC;
		}

	}
}

int InputLocal::GetPlayerInput()
{
	return KeyState;
}