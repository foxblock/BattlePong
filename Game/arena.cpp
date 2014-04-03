
#include "arena.h"
#include "ball.h"
#include "player.h"
#include "../Framework/framework.h"

Arena::Arena()
{
	RoofY = 10;
	FloorY = Framework::System->GetDisplayHeight() - 36;
	Player1WallX = 0;
	Player2WallX = Framework::System->GetDisplayWidth();
	PlayerFromWallX = 20;

	PlayBall = new Ball( this );
	Player1 = 0;
	Player2 = 0;
}

void Arena::EventOccurred( Event *e )
{
	if( Player1 != 0 )
	{
		Player1->GetInputSource()->EventOccurred(e);
	}
	if( Player2 != 0 )
	{
		Player2->GetInputSource()->EventOccurred(e);
	}
}

void Arena::Update()
{
	PlayBall->Update();
	if( Player1 != 0 )
	{
		Player1->Update();
	}
	if( Player2 != 0 )
	{
		Player2->Update();
	}
}

void Arena::Render()
{
	float healthWMax = Framework::System->GetDisplayWidth() / 2;
	float healthW;
	Uint32 healthC;

	spClearTarget( spGetFastRGB( 0, 0, 0 ) );
	spSetHorizontalOrigin( SP_LEFT );
	spSetVerticalOrigin( SP_TOP );
	spRectangle( 0, 6, -1, Framework::System->GetDisplayWidth(), 4, spGetFastRGB( 255, 255, 255 ) );
	spRectangle( 0, Framework::System->GetDisplayHeight() - 36, -1, Framework::System->GetDisplayWidth(), 4, spGetFastRGB( 255, 255, 255 ) );

	spSetHorizontalOrigin( SP_CENTER );
	spSetVerticalOrigin( SP_CENTER );
	for( int y = 0; y < (Framework::System->GetDisplayHeight() - 36) / 10; y++ )
	{
		spRectangle( Framework::System->GetDisplayWidth() / 2, (Framework::System->GetDisplayHeight() / 10) * y, -1, 4, Framework::System->GetDisplayHeight() / 15, spGetFastRGB( 255, 255, 255 ) );
	}
	spSetHorizontalOrigin( SP_LEFT );
	spSetVerticalOrigin( SP_TOP );
	spRectangle( 0, 0, -1, Framework::System->GetDisplayWidth(), 6, spGetFastRGB( 0, 0, 0 ) );
	spRectangle( 0, Framework::System->GetDisplayHeight() - 32, -1, Framework::System->GetDisplayWidth(), 32, spGetFastRGB( 0, 0, 0 ) );


	if( Player1 != 0 )
	{
		spSetHorizontalOrigin( SP_LEFT );
		spSetVerticalOrigin( SP_TOP );
		healthW = (float)Player1->Health / (float)PLAYER_MAX_HEALTH;
		if( healthW <= 0.2 )
		{
			healthC = spGetFastRGB( 220, 80, 80 );
		} else if( healthW <= 0.5 ) {
			healthC = spGetFastRGB( 220, 220, 80 );
		} else {
			healthC = spGetFastRGB( 80, 220, 80 );
		}
		spRectangle( 0, 0, -1, healthW * healthWMax, 6, healthC );

		Player1->Render();
	}
	if( Player2 != 0 )
	{
		spSetHorizontalOrigin( SP_RIGHT );
		spSetVerticalOrigin( SP_TOP );
		healthW = (float)Player2->Health / (float)PLAYER_MAX_HEALTH;
		if( healthW <= 0.2 )
		{
			healthC = spGetFastRGB( 220, 80, 80 );
		} else if( healthW <= 0.5 ) {
			healthC = spGetFastRGB( 220, 220, 80 );
		} else {
			healthC = spGetFastRGB( 80, 220, 80 );
		}
		spRectangle( Framework::System->GetDisplayWidth(), 0, -1, healthW * healthWMax, 6, healthC );

		Player2->Render();
	}
	PlayBall->Render();
}
