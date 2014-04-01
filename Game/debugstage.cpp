
#include "debugstage.h"
#include "../Framework/framework.h"
#include "menu.h"
#include "../Transitions/strips.h" // fade.h"

void DebugStage::Begin()
{
	ballPosition = new Vector2( Framework::System->GetDisplayWidth() / 2.0f, Framework::System->GetDisplayHeight() / 2.0f );
	ballDirection = new Angle( 30 ); // rand() % 360 );
	ballVelocity = 7.0f;
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
			Framework::System->ProgramStages->Push( new TransitionStrips( 120, 6 ) );
		}
		if( e->Data.Keyboard.keysym.sym == SDLK_HOME )
		{
			ballVelocity = ballVelocity - 0.5f;
		}
		if( e->Data.Keyboard.keysym.sym == SDLK_END )
		{
			ballVelocity = ballVelocity + 0.5f;
		}
	}
}

void DebugStage::Update()
{
	Vector2* v = new Vector2( ballDirection->ToDegrees() );
	v->Multiply( ballVelocity );
	ballPosition->Add( v );
	delete v;

	if( ballPosition->X < 0 )
	{
		ballPosition->X = abs(ballPosition->X);
		if( ballDirection->ToDegrees() < 180.0f )
		{
			ballDirection->Add( ballDirection->ShortestAngleTo(90.0f) * -2.0f );
		} else {
			ballDirection->Add( (270.0f - ballDirection->ToDegrees()) * 2.0f );
		}
	}
	if( ballPosition->X >= Framework::System->GetDisplayWidth() )
	{
		ballPosition->X -= ballPosition->X - Framework::System->GetDisplayWidth();
		if( ballDirection->ToDegrees() > 270.0f )
		{
			ballDirection->Add( ballDirection->ShortestAngleTo(270.0f) * -2.0f );
		} else {
			ballDirection->Add( 180.0f - (ballDirection->ToDegrees() * 2.0f) );
		}
	}
	if( ballPosition->Y < 0 )
	{
		ballPosition->Y = abs(ballPosition->Y);
		if( ballDirection->ToDegrees() < 270.0f )
		{
			ballDirection->Add( ballDirection->ShortestAngleTo(180.0f) * -2.0f );
		} else {
			ballDirection->Add( (360.0f - ballDirection->ToDegrees()) * 2.0f );
		}
	}
	if( ballPosition->Y >= Framework::System->GetDisplayHeight() )
	{
		ballPosition->Y -= ballPosition->Y - Framework::System->GetDisplayHeight();
		if( ballDirection->ToDegrees() > 90.0f )
		{
			ballDirection->Add( ballDirection->ShortestAngleTo(180.0f) * 2.0f );
		} else {
			ballDirection->Add( 360.0f - (ballDirection->ToDegrees() * 2.0f) );
		}

	}
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

	spEllipse( ballPosition->X, ballPosition->Y, -1, 10, 10, spGetFastRGB( 255, 255, 255 ) );
}

bool DebugStage::StageIsTransition()
{
	return false;
}
