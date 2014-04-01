
#pragma once

#include "../Framework/stage.h"
#include "../Framework/graphicslib.h"
#include "../Library/spritesheet.h"

class TransitionStrips : public Stage
{
	private:
		bool FadeToNewStage;
		Stage* Source;
		Stage* Target;
		int numStrips;
		int frameIndex;
		int frameMax;
		SDL_Surface* SourceScreen;
		SDL_Surface* TargetScreen;
		int stripWidth;
		int slowestSpeed;
		int* speedList;

		void PrepareStrips( Uint16 FadeFrames, Uint16 NumberOfStrips );

  public:
		TransitionStrips( Uint16 FadeFrames, Uint16 NumberOfStrips );	// Fade back to previous stack
		TransitionStrips( Stage* FadeInTo, Uint16 FadeFrames, Uint16 NumberOfStrips );		// Fade into new stage
		~TransitionStrips();

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
