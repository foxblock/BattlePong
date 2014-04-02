
#include "arena.h"
#include "ball.h"
#include "player.h"
#include "../Framework/framework.h"

Arena::Arena()
{
	RoofY = 10;
	FloorY = Framework::System->GetDisplayHeight() - 20;
	Player1WallX = 0;
	Player2WallX = Framework::System->GetDisplayWidth();
	PlayerFromWallX = 10;

	PlayBall = new Ball( this );
	Player1 = new Player( this, true );
	Player2 = new Player( this, false );
}

void Arena::Update()
{
	PlayBall->Update();
}

void Arena::Render()
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

	PlayBall->Render();
	Player1->Render();
	Player2->Render();
}
