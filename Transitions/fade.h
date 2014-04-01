
#pragma once

#include "../Framework/stage.h"
#include "../Framework/graphicslib.h"
#include "../Library/spritesheet.h"

class TransitionFade : public Stage
{
	private:
		bool FadeToNewStage;
		Stage* Source;
		Stage* Target;
		int Alpha;
		int FadePerUpdate;
		SDL_Surface* SourceScreen;
		SDL_Surface* TargetScreen;

		void PrepareFade( Uint16 FadeFrames );

  public:
		TransitionFade( Uint16 FadeFrames );	// Fade back to previous stack
		TransitionFade( Stage* FadeInTo, Uint16 FadeFrames );		// Fade into new stage
		~TransitionFade();

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
