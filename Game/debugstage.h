
#pragma once

#include "../Framework/stage.h"
#include "../Framework/graphicslib.h"
#include "../Library/spritesheet.h"
#include "../Library/vector2.h"

class DebugStage : public Stage
{
	private:
		Vector2* ballPosition;
		Angle* ballDirection;
		float ballVelocity;

		int roofY;
		int floorY;
		int player1wallX;
		int player2wallX;

  public:
    // Stage control
    virtual void Begin();
    virtual void Pause();
    virtual void Resume();
    virtual void Finish();
    virtual void EventOccurred(Event *e);
    virtual void Update();
    virtual void Render();
		virtual bool StageIsTransition();
};