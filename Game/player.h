
#pragma once

#ifndef Arena
class Arena;
#endif

#define PLAYER_MAX_HEALTH		10

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

};