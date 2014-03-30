
#pragma once

#include "../Framework/stage.h"
#include "../Framework/graphicslib.h"
#include "../Library/spritesheet.h"

class TransitionFadeAcross : public Stage
{
	private:
		Stage* Target;
		int Alpha;
		int FadePerUpdate;

  public:
		TransitionFadeAcross( Stage* FadeInTo, Uint16 FadeFrames );
		~TransitionFadeAcross();

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
