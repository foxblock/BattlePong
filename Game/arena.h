
#pragma once

#include "../Framework/event.h"

#ifndef Player
class Player;
#endif

#ifndef Ball
class Ball;
#endif

class Arena
{

	public:
		int RoofY;
		int FloorY;
		int Player1WallX;
		int Player2WallX;
		int PlayerFromWallX;

		Player* Player1;
		Player* Player2;
		Ball* PlayBall;

		Arena();

		void EventOccurred(Event *e);
		void Update();
		void Render();

};