
#include "ball.h"
#include "arena.h"
#include "../Framework/framework.h"

Ball::Ball( Arena* PlayingArena )
{
	gameArena = PlayingArena;
	ballPosition = new Vector2( ((gameArena->Player2WallX - gameArena->Player1WallX) / 2.0f) + gameArena->Player1WallX, ((gameArena->FloorY - gameArena->RoofY) / 2.0f) + gameArena->RoofY );
	ballDirection = new Angle( rand() % 360 );
	ballVelocity = (rand() % 10) + 4;
}

void Ball::Update()
{
	Vector2* v = new Vector2( ballDirection->ToDegrees() );
	v->Multiply( ballVelocity );
	ballPosition->Add( v );
	delete v;

	if( ballPosition->X < gameArena->Player1WallX )
	{
		ballPosition->X = gameArena->Player1WallX - (ballPosition->X - gameArena->Player1WallX);
		if( ballDirection->ToDegrees() < 180.0f )
		{
			ballDirection->Add( ballDirection->ShortestAngleTo(90.0f) * -2.0f );
		} else {
			ballDirection->Add( (270.0f - ballDirection->ToDegrees()) * 2.0f );
		}
		// TODO: Hurt player 1
	}
	if( ballPosition->X >= gameArena->Player2WallX )
	{
		ballPosition->X -= ballPosition->X - gameArena->Player2WallX;
		if( ballDirection->ToDegrees() > 270.0f )
		{
			ballDirection->Add( ballDirection->ShortestAngleTo(270.0f) * -2.0f );
		} else {
			ballDirection->Add( 180.0f - (ballDirection->ToDegrees() * 2.0f) );
		}
		// TODO: Hurt player 2
	}
	if( ballPosition->Y < gameArena->RoofY )
	{
		ballPosition->Y = gameArena->RoofY - (ballPosition->Y - gameArena->RoofY);
		if( ballDirection->ToDegrees() < 270.0f )
		{
			ballDirection->Add( ballDirection->ShortestAngleTo(180.0f) * -2.0f );
		} else {
			ballDirection->Add( (360.0f - ballDirection->ToDegrees()) * 2.0f );
		}
	}
	if( ballPosition->Y >= gameArena->FloorY )
	{
		ballPosition->Y -= ballPosition->Y - gameArena->FloorY;
		if( ballDirection->ToDegrees() > 90.0f )
		{
			ballDirection->Add( ballDirection->ShortestAngleTo(180.0f) * 2.0f );
		} else {
			ballDirection->Add( 360.0f - (ballDirection->ToDegrees() * 2.0f) );
		}
	}

	// TODO: Check collisions with players
}

void Ball::Render()
{
	spEllipse( ballPosition->X, ballPosition->Y, -1, 6, 6, spGetFastRGB( 255, 255, 255 ) );
}
