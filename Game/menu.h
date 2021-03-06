
#pragma once

#include "../Framework/stage.h"
#include "../Framework/graphicslib.h"
#include "../Library/spritesheet.h"

class Menu : public Stage
{
	private:
		int selectedItem;
		static int selectedSway[16];
		int selectedSwayIndex;
		int selectedSwayDelay;
		spFont* fontTitle;
		spFont* fontMenuUnselected;
		spFont* fontMenuSelected;
		spFont* fontMenuDisabled;

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