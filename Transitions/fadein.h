
#pragma once

#include "../Framework/stage.h"
#include "../Framework/graphicslib.h"
#include "../Library/spritesheet.h"

class TransitionFadeIn : public Stage
{
	private:
		Stage* Target;
		int Alpha;

  public:
		TransitionFadeIn( Stage* FadeInTo );
		~TransitionFadeIn();

    // Stage control
    virtual void Begin();
    virtual void Pause();
    virtual void Resume();
    virtual void Finish();
    virtual void EventOccurred(Event *e);
    virtual void Update();
    virtual void Render();
};
