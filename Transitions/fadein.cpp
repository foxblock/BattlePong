
#include "fadein.h"
#include "../Framework/framework.h"

TransitionFadeIn::TransitionFadeIn( Stage* FadeInTo )
{
	Target = FadeInTo;
	Target->Begin();
	Alpha = 0;
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
	Alpha += SP_ONE / 20;
	if( Alpha >= SP_ONE )
	{
		Stage* t = Target;
		delete Framework::System->ProgramStages->Pop();
		t->Finish();
		Framework::System->ProgramStages->Push( t );
	}
}

void TransitionFadeIn::Render()
{
	SDL_Surface* b = spGetWindowSurface();
	SDL_Surface* t = spUniqueCopySurface( spGetWindowSurface() );

	spClearTarget( spGetFastRGB( 0, 0, 0 ) );

	spSetHorizontalOrigin( SP_TOP );
	spSetVerticalOrigin( SP_LEFT );

	spSelectRenderTarget( t );
	Target->Render();
	spSelectRenderTarget( b );

	spSetBlending( Alpha );
	spBlitSurface( 0, 0, -1, t );

	spSetBlending( SP_ONE );
	spDeleteSurface( t );
}
