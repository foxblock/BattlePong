
#include "fadeacross.h"
#include "../Framework/framework.h"

TransitionFadeAcross::TransitionFadeAcross( Stage* FadeInTo, Uint16 FadeFrames )
{
	Target = FadeInTo;
	Target->Begin();
	Alpha = 0;
	FadePerUpdate = SP_ONE / FadeFrames;
}

TransitionFadeAcross::~TransitionFadeAcross()
{
}

void TransitionFadeAcross::Begin()
{
}

void TransitionFadeAcross::Pause()
{
}

void TransitionFadeAcross::Resume()
{
}

void TransitionFadeAcross::Finish()
{
}

void TransitionFadeAcross::EventOccurred(Event *e)
{
}

void TransitionFadeAcross::Update()
{
	Alpha += FadePerUpdate;
	if( Alpha >= SP_ONE )
	{
		// Swap to new stage
		Stage* t = Target;
		delete Framework::System->ProgramStages->Pop();
		t->Finish();
		Framework::System->ProgramStages->Push( t );
	} else {
		// Allow the target stage to process updates, so any animations will run
		Target->Update();
	}
}

void TransitionFadeAcross::Render()
{
	SDL_Surface* b = spGetWindowSurface();
	SDL_Surface* t = spUniqueCopySurface( b );

	// Fade from previous stage
	Framework::System->ProgramStages->Previous( this )->Render();

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
