#include "greyscale.h"

ShaderGreyscale::ShaderGreyscale()
{
}

ShaderGreyscale::~ShaderGreyscale()
{
}

void ShaderGreyscale::Apply( SDL_Surface* Target )
{
	// Luminance = (unsigned char)(((float)gsCol->r * 0.35) + ((float)gsCol->g * 0.5) + ((float)gsCol->b * 0.15));
	ShaderARBG* map = GetARGBMap( Target );

	for( int y = 0; y < Target->h; y++ )
	{
		for( int x = 0; x < Target->w; x++ )
		{
			ShaderARBG pxl = map[(y * Target->w) + x];
#ifdef PANDORA
			map[(y * Target->w) + x].r = (pxl.r >> 2) + (pxl.g >> 1) + (pxl.b >> 3);	// Faster but inaccurate
#else
			map[(y * Target->w) + x].r = ((float)pxl.r * 0.35f) + ((float)pxl.g * 0.5) + ((float)pxl.b * 0.15f);
#endif
			map[(y * Target->w) + x].g = map[(y * Target->w) + x].r;
			map[(y * Target->w) + x].b = map[(y * Target->w) + x].r;

		}
	}

	SetARGBMap( Target, map );
}
