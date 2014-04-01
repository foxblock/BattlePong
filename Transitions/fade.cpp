
#include "fade.h"
#include "../Framework/framework.h"

TransitionFade::TransitionFade( Uint16 FadeFrames )
{
	FadeToNewStage = false;
	Source = Framework::System->ProgramStages->Current();	// This stage won't be on the stack when the constructor is called
	Target = Framework::System->ProgramStages->Previous( Source );
	PrepareFade( FadeFrames );
}

TransitionFade::TransitionFade( Stage* FadeInTo, Uint16 FadeFrames )
{
	FadeToNewStage = true;
	Source = Framework::System->ProgramStages->Current();	// This stage won't be on the stack when the constructor is called
	Target = FadeInTo;
	Target->Begin();
	Target->Pause();
	PrepareFade( FadeFrames );
}

void TransitionFade::PrepareFade( Uint16 FadeFrames )
{
	Alpha = 0;
	FadePerUpdate = SP_ONE / FadeFrames;
	SourceScreen = spUniqueCopySurface( spGetWindowSurface() );
	spSelectRenderTarget( SourceScreen );
	Source->Render();
	TargetScreen = spUniqueCopySurface( spGetWindowSurface() );
	spSelectRenderTarget( TargetScreen );
	Target->Render();
	spSelectRenderTarget( spGetWindowSurface() );
}

TransitionFade::~TransitionFade()
{
	if( SourceScreen != 0 )
	{
		spDeleteSurface( SourceScreen );
	}
	if( TargetScreen != 0 )
	{
		spDeleteSurface( TargetScreen );
	}
}

void TransitionFade::Begin()
{
}

void TransitionFade::Pause()
{
}

void TransitionFade::Resume()
{
}

void TransitionFade::Finish()
{
}

void TransitionFade::EventOccurred(Event *e)
{
}

void TransitionFade::Update()
{
	Alpha += FadePerUpdate;
	if( Alpha >= SP_ONE )
	{
		Stage* t = Target;
		if( FadeToNewStage )
		{
			// Swap to new stage
			delete Framework::System->ProgramStages->Pop();		// Remove transition stage (this)
			t->Resume();
			t->Finish();
			Framework::System->ProgramStages->Push( t );
		} else {
			// Pop off back to stage
			while( Framework::System->ProgramStages->Current() != t )
			{
				delete Framework::System->ProgramStages->Pop();
			}
		}
	}
}

void TransitionFade::Render()
{
	spSetHorizontalOrigin( SP_LEFT );
	spSetVerticalOrigin( SP_TOP );

	// Draw original source
	spSetBlending( SP_ONE );
	spBlitSurface( 0, 0, -1, SourceScreen );
	// Alpha it to the actual screen
	spSetBlending( Alpha );
	spBlitSurface( 0, 0, -1, TargetScreen );
	spSetBlending( SP_ONE );
}

bool TransitionFade::StageIsTransition()
{
	return true;
}
