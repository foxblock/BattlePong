
#include "debugstage.h"
#include "../Framework/framework.h"
#include "menu.h"
#include "../Transitions/strips.h" // fade.h"
#include "player.h"

void DebugStage::Begin()
{
	playArena = new Arena();
	playArena->Player1 = new Player( playArena, true, PlayerInputSource::LOCAL_INPUT );
	playArena->Player2 = new Player( playArena, false, PlayerInputSource::NO_INPUT );

}

void DebugStage::Pause()
{
}

void DebugStage::Resume()
{
}

void DebugStage::Finish()
{
}

void DebugStage::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.keysym.sym == SDLK_ESCAPE )
		{
			Framework::System->ProgramStages->Push( new TransitionStrips( 40, 24 ) );
			return;
		}
	}
	playArena->EventOccurred( e );
}

void DebugStage::Update()
{
	playArena->Update();
}

void DebugStage::Render()
{
	playArena->Render();
}

bool DebugStage::StageIsTransition()
{
	return false;
}
