
#pragma once

#include "../Library/angle.h"
#include "../Library/vector2.h"

#ifndef Arena
class Arena;
#endif

class Ball
{
	private:
		Arena* gameArena;
		Vector2* ballPosition;
		Angle* ballDirection;
		float ballVelocity;
		int ballRadius;

	public:
		Ball(Arena* PlayingArena);
		void Update();
		void Render();

};