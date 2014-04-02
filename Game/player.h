
#pragma once

#ifndef Arena
class Arena;
#endif

#define PLAYER_MAX_HEALTH			10

#define PLAYER_CONTROLS_NONE	0
#define PLAYER_CONTROLS_UP		1
#define PLAYER_CONTROLS_DOWN	2
#define PLAYER_CONTROLS_SEND	4
#define PLAYER_CONTROLS_USEA	8
#define PLAYER_CONTROLS_USEB	16
#define PLAYER_CONTROLS_USEC	32

class Player
{
	private:
		Arena* gameArena;
		float reboundDirection;


	public:
		int Health;
		int Position;
		bool FacesLeft;
		int PowerUps[3];

		Player(Arena* PlayingArena, bool LeftSide);
		void Render();
		bool DoesCollideWithBall();
		float GetCollisionReboundDirection();

		virtual int GetPlayerInput();

};