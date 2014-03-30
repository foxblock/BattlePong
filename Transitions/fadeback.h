
#pragma once

#include "../Framework/stage.h"
#include "../Framework/graphicslib.h"
#include "../Library/spritesheet.h"

class TransitionFadeBack : public Stage
{
	private:
		Stage* Target;
		Stage* Source;
		int Alpha;
		int FadePerUpdate;

  public:
		TransitionFadeBack( Uint16 FadeFrames );
		~TransitionFadeBack();

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
