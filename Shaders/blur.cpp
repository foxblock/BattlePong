
#include "blur.h"

ShaderBlur::ShaderBlur()
{
}

ShaderBlur::~ShaderBlur()
{
}

void ShaderBlur::Apply( SDL_Surface* Target )
{
	// Keep render target (might not be applying shader to screen)
	SDL_Surface* r = spGetRenderTarget();

	SDL_Surface* t = spUniqueCopySurface( Target );
	
	spSetHorizontalOrigin( SP_LEFT );
	spSetVerticalOrigin( SP_TOP );

	spSelectRenderTarget( t );
	spSetBlending( SP_ONE );
	spBlitSurface( 0, 0, -1, Target );
	spSetBlending( SP_ONE >> 2 );
	for( int y = -1; y <= 1; y++ )
	{
		for( int x = -1; x <= 1; x++ )
		{
			if( x != 0 && y != 0 )
			{
				spBlitSurface( x, y, -1, Target );
			}
		}
	}

	spSelectRenderTarget( Target );
	spSetBlending( SP_ONE );
	spBlitSurface( 0, 0, -1, t );

	spDeleteSurface( t );

	// Restore render target
	spSelectRenderTarget( r );
}
