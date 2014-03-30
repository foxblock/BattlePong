
#pragma once

#include "../Framework/graphicslib.h"

class Shader
{
	protected:
		Uint32 GetPixel32( SDL_Surface* surface, int x, int y );
		Uint32 GetPixel24( SDL_Surface* surface, int x, int y );
		Uint32 GetPixel16( SDL_Surface* surface, int x, int y );
		void SetPixel32( SDL_Surface* surface, int x, int y, Uint32 color );
		void SetPixel24( SDL_Surface* surface, int x, int y, Uint32 color );
		void SetPixel16( SDL_Surface* surface, int x, int y, Uint32 color );

	public:
		virtual void Apply( SDL_Surface* Target ) = 0;
		Uint32 GetPixel( SDL_Surface* surface, int x, int y );
		void SetPixel( SDL_Surface* surface, int x, int y, Uint32 color );
};