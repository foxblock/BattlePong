
#include "fadein.h"
#include "../Framework/framework.h"

TransitionFadeIn::TransitionFadeIn( Uint16 FadeFromColour, Stage* FadeInTo, Uint16 FadeFrames )
{
	SourceColour = FadeFromColour;
	Target = FadeInTo;
	Target->Begin();
	Alpha = 0;
	FadePerUpdate = SP_ONE / FadeFrames;
}

TransitionFadeIn::~TransitionFadeIn()
{
}

void TransitionFadeIn::Begin()
{
}

void TransitionFadeIn::Pause()
{
}

void TransitionFadeIn::Resume()
{
}

void TransitionFadeIn::Finish()
{
}

void TransitionFadeIn::EventOccurred(Event *e)
{
}

void TransitionFadeIn::Update()
{
	Alpha += FadePerUpdate;
	if( Alpha >= SP_ONE )
	{
		// Swap to new stage
		Stage* t = Target;
		delete Framework::System->ProgramStages->Pop();		// Remove transition stage (this)
		t->Finish();
		Framework::System->ProgramStages->Push( t );
	} else {
		// Allow the target stage to process updates, so any animations will run
		Target->Update();
	}
}

void TransitionFadeIn::Render()
{
	SDL_Surface* b = spGetWindowSurface();
	SDL_Surface* t = spUniqueCopySurface( b );

	// Fade from colour
	spClearTarget( SourceColour );

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

bool TransitionFadeIn::StageIsTransition()
{
	return true;
}
