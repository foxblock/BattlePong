
#include "player.h"
#include "arena.h"

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