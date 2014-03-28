
#include "spritesheet.h"

SpriteSheet::SpriteSheet( SDL_Surface* SheetGraphic )
{
	sheet = SheetGraphic;
	deleteSurfaceAtDestroy = true;
}

SpriteSheet::SpriteSheet( SDL_Surface* SheetGraphic, bool KeepSurface )
{
	sheet = SheetGraphic;
	deleteSurfaceAtDestroy = !KeepSurface;
}

SpriteSheet::SpriteSheet( SDL_Surface* SheetGraphic, int FrameWidth, int FrameHeight )
{
	int x;
	int y;

	sheet = SheetGraphic;
	deleteSurfaceAtDestroy = true;

	for( y = 0; y < sheet->h; y += FrameHeight )
	{
		for( x = 0; x < sheet->w; x += FrameWidth )
		{
			AddSprite( x, y, FrameWidth, FrameHeight );
		}
	}
}

SpriteSheet::SpriteSheet( SDL_Surface* SheetGraphic, int FrameWidth, int FrameHeight, bool KeepSurface )
{
	int x;
	int y;

	sheet = SheetGraphic;
	deleteSurfaceAtDestroy = !KeepSurface;

	for( y = 0; y < sheet->h; y += FrameHeight )
	{
		for( x = 0; x < sheet->w; x += FrameWidth )
		{
			AddSprite( x, y, FrameWidth, FrameHeight );
		}
	}
}

SpriteSheet::~SpriteSheet()
{
	if( deleteSurfaceAtDestroy )
	{
		spDeleteSurface( sheet );
	}
}

SDL_Surface* SpriteSheet::GetSheet()
{
	return sheet;
}

int SpriteSheet::AddSprite( int FrameX, int FrameY, int FrameWidth, int FrameHeight )
{
	SDL_Rect* r = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
	r->x = FrameX;
	r->y = FrameY;
	r->w = FrameWidth;
	r->h = FrameHeight;
	frames.push_back( r );
	return frames.size() - 1;
}

void SpriteSheet::DrawSprite( int FrameNumber, int ScreenX, int ScreenY, float ScaleX, float ScaleY, Angle* Rotation )
{
	if( FrameNumber < 0 || FrameNumber >= (int)frames.size() )
	{
		return;
	}

	SDL_Rect* r = frames.at( FrameNumber );
	if( Rotation == 0 )
	{
		spRotozoomSurfacePart( ScreenX, ScreenY, -1, sheet, r->x, r->y, r->w,	r->h, ScaleX * SP_ONE, ScaleY * SP_ONE, 0 );
	} else {
		spRotozoomSurfacePart( ScreenX, ScreenY, -1, sheet, r->x, r->y, r->w,	r->h, ScaleX * SP_ONE, ScaleY * SP_ONE, Rotation->ToRadiansSparrow() );
	}
}

