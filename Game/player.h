
#pragma once

#include "input/iinput.h"

#ifndef Arena
class Arena;
#endif

#define PLAYER_MAX_HEALTH			10

namespace PlayerInputSource
{
	enum InputSources
	{
		NO_INPUT = 0,
		LOCAL_INPUT = 1,
		COMPUTER_AI_EASY = 2,
		COMPUTER_AI_MEDIUM = 3,
		COMPUTER_AI_HARD = 4,
		NETWORK = 5
	};
};

class Player
{
	private:
		Arena* gameArena;
		float reboundDirection;
		IInput* InputSource;

	public:
		int Health;
		int Position;
		bool FacesLeft;
		int PowerUps[3];


		Player(Arena* PlayingArena, bool LeftSide, PlayerInputSource::InputSources Source);
		void Update();
		void Render();

		IInput* GetInputSource();
		bool DoesCollideWithBall();
		float GetCollisionReboundDirection();

};