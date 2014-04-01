
#include "strips.h"
#include "../Framework/framework.h"

TransitionStrips::TransitionStrips( Uint16 FadeFrames, Uint16 NumberOfStrips )
{
	FadeToNewStage = false;
	Source = Framework::System->ProgramStages->Current();	// This stage won't be on the stack when the constructor is called
	Target = Framework::System->ProgramStages->Previous( Source );
	PrepareStrips( FadeFrames, NumberOfStrips );
}

TransitionStrips::TransitionStrips( Stage* FadeInTo, Uint16 FadeFrames, Uint16 NumberOfStrips )
{
	FadeToNewStage = true;
	Source = Framework::System->ProgramStages->Current();	// This stage won't be on the stack when the constructor is called
	Target = FadeInTo;
	Target->Begin();
	Target->Pause();
	PrepareStrips( FadeFrames, NumberOfStrips );
}

void TransitionStrips::PrepareStrips( Uint16 FadeFrames, Uint16 NumberOfStrips )
{
	numStrips = NumberOfStrips;
	frameMax = FadeFrames;
	stripWidth = Framework::System->GetDisplayWidth() / NumberOfStrips;
	if( stripWidth * NumberOfStrips < Framework::System->GetDisplayWidth() )	// Correct any rounding issues
	{
		stripWidth++;
	}
	frameIndex = 0;
	slowestSpeed = Framework::System->GetDisplayHeight() / FadeFrames;
	SourceScreen = spUniqueCopySurface( spGetWindowSurface() );
	spSelectRenderTarget( SourceScreen );
	Source->Render();
	TargetScreen = spUniqueCopySurface( spGetWindowSurface() );
	spSelectRenderTarget( TargetScreen );
	Target->Render();
	spSelectRenderTarget( spGetWindowSurface() );

	speedList = (int*)malloc( sizeof(int) * NumberOfStrips );
	for( int i = 0; i < NumberOfStrips; i++ )
	{
		speedList[i] = slowestSpeed + (rand() % slowestSpeed);
		if( speedList[i] == 0 )
		{
			speedList[i] = 1;
		}
	}
}

TransitionStrips::~TransitionStrips()
{
	free( (void*)speedList );
	if( SourceScreen != 0 )
	{
		spDeleteSurface( SourceScreen );
	}
	if( TargetScreen != 0 )
	{
		spDeleteSurface( TargetScreen );
	}
}

void TransitionStrips::Begin()
{
}

void TransitionStrips::Pause()
{
}

void TransitionStrips::Resume()
{
}

void TransitionStrips::Finish()
{
}

void TransitionStrips::EventOccurred(Event *e)
{
}

void TransitionStrips::Update()
{
	frameIndex++;
	if( frameIndex >= frameMax )
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

void TransitionStrips::Render()
{
	spSetHorizontalOrigin( SP_LEFT );
	spSetVerticalOrigin( SP_TOP );

	// Draw original source
	spBlitSurface( 0, 0, -1, SourceScreen );

	// Draw strips
	for( int i = 0; i < numStrips; i++ )
	{
		spBlitSurfacePart( i * stripWidth, 0, -1, TargetScreen, i * stripWidth, 0, stripWidth, speedList[i] * frameIndex );
	}
}

bool TransitionStrips::StageIsTransition()
{
	return true;
}
