
#pragma once

#include "../Framework/graphicslib.h"
#include <vector>
#include "angle.h"

class SpriteSheet
{
	private:
		SDL_Surface* sheet;
		std::vector<SDL_Rect*> frames;
		bool deleteSurfaceAtDestroy;

	public:
		SpriteSheet( SDL_Surface* SheetGraphic );
		SpriteSheet( SDL_Surface* SheetGraphic, bool KeepSurface );
		SpriteSheet( SDL_Surface* SheetGraphic, int FrameWidth, int FrameHeight );
		SpriteSheet( SDL_Surface* SheetGraphic, int FrameWidth, int FrameHeight, bool KeepSurface );
		~SpriteSheet();

		SDL_Surface* GetSheet();

		int AddSprite( int FrameX, int FrameY, int FrameWidth, int FrameHeight );
		void DrawSprite( int FrameNumber, int ScreenX, int ScreenY, float ScaleX, float ScaleY, Angle* Rotation );

};