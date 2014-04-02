
#include "debugstage.h"
#include "../Framework/framework.h"
#include "menu.h"
#include "../Transitions/strips.h" // fade.h"

void DebugStage::Begin()
{
	playArena = new Arena();
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
			//delete Framework::System->ProgramStages->Pop();
			Framework::System->ProgramStages->Push( new TransitionStrips( 40, 12 ) );
		}
		if( e->Data.Keyboard.keysym.sym == SDLK_HOME )
		{
			//ballVelocity = ballVelocity - 0.5f;
		}
		if( e->Data.Keyboard.keysym.sym == SDLK_END )
		{
			//ballVelocity = ballVelocity + 0.5f;
		}
	}
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
