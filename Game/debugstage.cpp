
#include "debugstage.h"
#include "../Framework/framework.h"
#include "menu.h"
#include "../Transitions/fadein.h"

void DebugStage::Begin()
{
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
			delete Framework::System->ProgramStages->Pop();
		}
	}
}

void DebugStage::Update()
{
}

void DebugStage::Render()
{
	spClearTarget( spGetFastRGB( 48, 128, 64 ) );
}
