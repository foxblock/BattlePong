
#include "player.h"
#include "arena.h"
#include "ball.h"
#include "../Framework/framework.h"

Player::Player( Arena* PlayingArena, bool LeftSide )
{
	Health = PLAYER_MAX_HEALTH;
	Position = ((PlayingArena->FloorY - PlayingArena->RoofY) / 2) + PlayingArena->RoofY;	// Centre
	gameArena = PlayingArena;
	FacesLeft = !LeftSide;
	PowerUps[0] = 0;
	PowerUps[1] = 0;
	PowerUps[2] = 0;
}

void Player::Render()
{
	int xPos = (FacesLeft ? gameArena->Player2WallX - gameArena->PlayerFromWallX : gameArena->Player1WallX + gameArena->PlayerFromWallX);
	spSetHorizontalOrigin( SP_CENTER );
	spSetVerticalOrigin( SP_CENTER );
	spRectangle( xPos, Position, -1, 8, 100, spGetFastRGB( 255, 255, 255 ) );
}

bool Player::DoesCollideWithBall()
{
	return false;
}

float Player::GetCollisionReboundDirection()
{
	// Calculated when checking collision
	return reboundDirection;
}

int Player::GetPlayerInput()
{
	return PLAYER_CONTROLS_NONE;
}
