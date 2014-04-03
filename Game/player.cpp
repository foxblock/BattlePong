
#include "player.h"
#include "arena.h"
#include "ball.h"
#include "../Framework/framework.h"
#include "input/input_none.h"
#include "input/input_local.h"
#include "input/input_ai_easy.h"
#include "input/input_ai_medium.h"
#include "input/input_ai_hard.h"
#include "input/input_network.h"

Player::Player( Arena* PlayingArena, bool LeftSide, PlayerInputSource::InputSources Source )
{
	Health = PLAYER_MAX_HEALTH;
	Position = ((PlayingArena->FloorY - PlayingArena->RoofY) / 2) + PlayingArena->RoofY;	// Centre
	gameArena = PlayingArena;
	FacesLeft = !LeftSide;
	PowerUps[0] = 0;
	PowerUps[1] = 0;
	PowerUps[2] = 0;

	switch( Source )
	{
		case PlayerInputSource::NO_INPUT:
			InputSource = new InputNone();
			break;
		case PlayerInputSource::LOCAL_INPUT:
			InputSource = new InputLocal( (LeftSide ? 1 : 2), true );		// TODO: Fix if Single player or not
			break;
		case PlayerInputSource::COMPUTER_AI_EASY:
			InputSource = new InputAIEasy();
			break;
		case PlayerInputSource::COMPUTER_AI_MEDIUM:
			InputSource = new InputAIMedium();
			break;
		case PlayerInputSource::COMPUTER_AI_HARD:
			InputSource = new InputAIHard();
			break;
		case PlayerInputSource::NETWORK:
			InputSource = new InputNetwork();
			break;
	}
}

void Player::Update()
{
	int Inputs = InputSource->GetPlayerInput();

	if( (Inputs & PLAYER_CONTROLS_UP) != 0 )
	{
		Position -= 4;
		if( (Position - 50) < gameArena->RoofY )
		{
			Position = gameArena->RoofY + 50;
		}
	}
	if( (Inputs & PLAYER_CONTROLS_DOWN) != 0 )
	{
		Position += 4;
		if( (Position + 50) > gameArena->FloorY )
		{
			Position = gameArena->FloorY - 50;
		}
	}
}

void Player::Render()
{
	int xPos = (FacesLeft ? gameArena->Player2WallX - gameArena->PlayerFromWallX : gameArena->Player1WallX + gameArena->PlayerFromWallX);
	spSetHorizontalOrigin( SP_CENTER );
	spSetVerticalOrigin( SP_CENTER );
	spRectangle( xPos, Position, -1, 8, 100, spGetFastRGB( 255, 255, 255 ) );
}

IInput* Player::GetInputSource()
{
	return InputSource;
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
