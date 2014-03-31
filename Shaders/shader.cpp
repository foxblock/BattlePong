
#include "shader.h"

Shader::Shader()
{
	// Create me a standardised pixel format (ignore platform endian)
	genericFormat.BitsPerPixel = 32;
	genericFormat.BytesPerPixel = 4;
	genericFormat.palette = 0;
	genericFormat.alpha = 255;
	genericFormat.colorkey = 0;
	genericFormat.Amask = 0xFF000000;
	genericFormat.Rmask = 0x00FF0000;
	genericFormat.Gmask = 0x0000FF00;
	genericFormat.Bmask = 0x000000FF;
	genericFormat.Ashift = 24;
	genericFormat.Rshift = 16;
	genericFormat.Gshift = 8;
	genericFormat.Bshift = 0;
	genericFormat.Aloss = 0;
	genericFormat.Rloss = 0;
	genericFormat.Gloss = 0;
	genericFormat.Bloss = 0;
}

ShaderARBG* Shader::GetARGBMap( SDL_Surface* surface )
{
	ShaderARBG* map = 0;
	SDL_Surface* converted;

	converted = SDL_ConvertSurface( surface, &genericFormat, SDL_SWSURFACE );
	if( converted == 0 )
	{
		return 0;
	}
	if( SDL_MUSTLOCK( converted ) )
	{
		if( SDL_LockSurface( converted ) < 0 )
		{
			spDeleteSurface( converted );
			return 0;
		}
	}

	map = (ShaderARBG*)malloc( converted->w * converted->h * genericFormat.BytesPerPixel );
	if( map != 0 )
	{
		if( converted->pitch == converted->w * genericFormat.BytesPerPixel )
		{
			// No pitch discrepancy, mass copy
			memcpy( (void*)map, converted->pixels, converted->pitch * converted->h );
		} else {
			// TODO: Fix to manually copy pixel data
			free( map );
			map = 0;
		}
	}

	if( SDL_MUSTLOCK( converted ) )
	{
		SDL_UnlockSurface( converted );
	}
	spDeleteSurface( converted );
	return map;
}

void Shader::SetARGBMap( SDL_Surface* surface, ShaderARBG* argbmap )
{
	SDL_Surface* temporary = 0;
	SDL_Surface* converted = 0;

	// Create surface from argb map
	temporary = SDL_CreateRGBSurfaceFrom( (void*)argbmap, surface->w, surface->h, 32, surface->w * genericFormat.BytesPerPixel, genericFormat.Rmask, genericFormat.Gmask, genericFormat.Bmask, genericFormat.Amask );
	if( temporary == 0 )
	{
		return;
	}

	// Convert surface to destination format
	converted = SDL_ConvertSurface( temporary, surface->format, SDL_SWSURFACE );
	spDeleteSurface( temporary );
	free( (void*)argbmap );
	if( converted == 0 )
	{
		return;
	}

	// Lock surfaces
	if( SDL_MUSTLOCK( converted ) )
	{
		if( SDL_LockSurface( converted ) < 0 )
		{
			spDeleteSurface( converted );
			return;
		}
	}
	if( SDL_MUSTLOCK( surface ) )
	{
		if( SDL_LockSurface( surface ) < 0 )
		{
			spDeleteSurface( converted );
			return;
		}
	}

	// Copy bit data
	memcpy( surface->pixels, converted->pixels, surface->h * surface->pitch );

	// Unlock and remove temporary surface
	if( SDL_MUSTLOCK( converted ) )
	{
		SDL_UnlockSurface( converted );
	}
	spDeleteSurface( converted );

	if( SDL_MUSTLOCK( surface ) )
	{
		SDL_UnlockSurface( surface );
	}
}
