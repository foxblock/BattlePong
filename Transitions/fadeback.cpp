
#include "fadeback.h"
#include "../Framework/framework.h"

TransitionFadeBack::TransitionFadeBack( Uint16 FadeFrames )
{
	Source = Framework::System->ProgramStages->Current();	// This stage won't be on the stack when the constructor is called
	Target = Framework::System->ProgramStages->Previous( Source );
	Alpha = 0;
	FadePerUpdate = SP_ONE / FadeFrames;
}

TransitionFadeBack::~TransitionFadeBack()
{
}

void TransitionFadeBack::Begin()
{
}

void TransitionFadeBack::Pause()
{
}

void TransitionFadeBack::Resume()
{
}

void TransitionFadeBack::Finish()
{
}

void TransitionFadeBack::EventOccurred(Event *e)
{
}

void TransitionFadeBack::Update()
{
	Alpha += FadePerUpdate;
	if( Alpha >= SP_ONE )
	{
		// Pop off back to stage
		Stage* t = Target;
		while( Framework::System->ProgramStages->Current() != t )
		{
			delete Framework::System->ProgramStages->Pop();
		}
	} else {
		// Allow the target stage to process updates, so any animations will run
		Target->Update();
	}
}

void TransitionFadeBack::Render()
{
	SDL_Surface* b = spGetWindowSurface();
	SDL_Surface* t = spUniqueCopySurface( b );

	// Fade from previous stage
	Source->Render();

	// Buffer the next stages screen
	spSelectRenderTarget( t );
	Target->Render();
	spSelectRenderTarget( b );

	// Alpha it to the actual screen
	spSetHorizontalOrigin( SP_LEFT );
	spSetVerticalOrigin( SP_TOP );
	spSetBlending( Alpha );
	spBlitSurface( 0, 0, -1, t );
	spSetBlending( SP_ONE );

	spDeleteSurface( t );
}

bool TransitionFadeBack::StageIsTransition()
{
	return true;
}
