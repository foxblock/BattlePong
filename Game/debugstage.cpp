
#include "debugstage.h"
#include "../Framework/framework.h"
#include "menu.h"
#include "../Transitions/fadeback.h"

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
			//delete Framework::System->ProgramStages->Pop();
			Framework::System->ProgramStages->Push( new TransitionFadeBack( 10 ) );
		}
	}
}

void DebugStage::Update()
{
}

void DebugStage::Render()
{
	spClearTarget( spGetFastRGB( 0, 0, 0 ) );
	spSetHorizontalOrigin( SP_LEFT );
	spSetVerticalOrigin( SP_TOP );
	spRectangle( 0, 4, -1, Framework::System->GetDisplayWidth(), 6, spGetFastRGB( 255, 255, 255 ) );
	spRectangle( 0, Framework::System->GetDisplayHeight() - 10, -1, Framework::System->GetDisplayWidth(), 6, spGetFastRGB( 255, 255, 255 ) );

	spSetHorizontalOrigin( SP_CENTER );
	spSetVerticalOrigin( SP_CENTER );
	for( int y = 0; y < (Framework::System->GetDisplayHeight() - 20) / 10; y++ )
	{
		spRectangle( Framework::System->GetDisplayWidth() / 2, (Framework::System->GetDisplayHeight() / 10) * y, -1, 4, Framework::System->GetDisplayHeight() / 15, spGetFastRGB( 255, 255, 255 ) );
	}
}

bool DebugStage::StageIsTransition()
{
	return false;
}
