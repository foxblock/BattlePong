
#include "greyscale.h"

ShaderGreyscale::ShaderGreyscale()
{
}

ShaderGreyscale::~ShaderGreyscale()
{
}

void ShaderGreyscale::Apply( SDL_Surface* Target )
{
	// Can't greyscale paletted surface
	if( Target->format->palette != 0 )
	{
		return;
	}

	// Can't lock surface for editing
	if( SDL_MUSTLOCK( Target ) )
	{
		if( SDL_LockSurface( Target ) < 0 )
		{
			return;
		}
	}

	Uint8 R, G, B, g;

	for( int y = 0; y < Target->h; y++ )
	{
		for( int x = 0; x < Target->w; x++ )
		{
			Uint32 col = GetPixel( Target, x, y );

		}
	}

	if( SDL_MUSTLOCK( Target ) )
	{
		SDL_UnlockSurface( Target );
	}
}
