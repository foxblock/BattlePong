
#include "ball.h"
#include "arena.h"
#include "player.h"
#include "../Framework/framework.h"
#include "../Library/line.h"

Ball::Ball( Arena* PlayingArena )
{
	gameArena = PlayingArena;
	ballPosition = new Vector2( ((gameArena->Player2WallX - gameArena->Player1WallX) / 2.0f) + gameArena->Player1WallX, ((gameArena->FloorY - gameArena->RoofY) / 2.0f) + gameArena->RoofY );
	ballDirection = new Angle( rand() % 360 );
	ballVelocity = 4.0f;
}

void Ball::Update()
{
	Vector2* prevPosition = new Vector2(ballPosition->X, ballPosition->Y);

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
		// Hurt Player 1
		if( gameArena->Player1 != 0 )
		{
			gameArena->Player1->TakeDamage( 2 );
		}
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
		// Hurt player 2
		if( gameArena->Player2 != 0 )
		{
			gameArena->Player2->TakeDamage( 2 );
		}
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

	// Check collisions with players
	Line* ballPath = new Line( prevPosition, ballPosition );
	Line* pArea = 0;
	if( ballDirection->ToDegrees() > 90.0f && ballDirection->ToDegrees() < 270.0f && gameArena->Player1 != 0 )
	{
		pArea = gameArena->Player1->GetCollisionLine();
	}
	if( (ballDirection->ToDegrees() < 90.0f || ballDirection->ToDegrees() > 270.0f) && gameArena->Player2 != 0 )
	{
		pArea = gameArena->Player2->GetCollisionLine();
	}
	if( pArea != 0 )
	{
		Vector2* pContact = ballPath->GetIntersection( pArea );
		if( pContact != 0 )
		{

			if( ballDirection->ToDegrees() < 180.0f && ballDirection->ToDegrees() > 90.0f )
			{
				ballDirection->Add( ballDirection->ShortestAngleTo(90.0f) * -2.0f );
				ballPosition->X += (pContact->X - ballPosition->X) * 2.0f;
			} else if( ballDirection->ToDegrees() >= 180.0f && ballDirection->ToDegrees() < 270.0f ) {
				ballDirection->Add( (270.0f - ballDirection->ToDegrees()) * 2.0f );
				ballPosition->X += (pContact->X - ballPosition->X) * 2.0f;
			} else if( ballDirection->ToDegrees() > 270.0f ) {
				ballDirection->Add( ballDirection->ShortestAngleTo(270.0f) * -2.0f );
				ballPosition->X -= (ballPosition->X - pContact->X) * 2.0f;
			} else if( ballDirection->ToDegrees() < 90.0f ) {
				ballDirection->Add( 180.0f - (ballDirection->ToDegrees() * 2.0f) );
				ballPosition->X -= (ballPosition->X - pContact->X) * 2.0f;
			}

		}
	}
	delete pArea;
	delete ballPath;

	delete prevPosition;
}

void Ball::Render()
{
	spEllipse( ballPosition->X, ballPosition->Y, -1, 6, 6, spGetFastRGB( 255, 255, 255 ) );
}
