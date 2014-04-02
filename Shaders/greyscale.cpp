#include "greyscale.h"

ShaderGreyscale::ShaderGreyscale()
{
}

ShaderGreyscale::~ShaderGreyscale()
{
}

void ShaderGreyscale::Apply( SDL_Surface* Target )
{
	ShaderARBG pxlLast = { 0, 0, 0, 0 };
	Uint8 greyLast;
	// Luminance = (unsigned char)(((float)gsCol->r * 0.35) + ((float)gsCol->g * 0.5) + ((float)gsCol->b * 0.15));
	ShaderARBG* map = GetARGBMap( Target );

	for( int y = 0; y < Target->h; y++ )
	{
		for( int x = 0; x < Target->w; x++ )
		{
			ShaderARBG pxl = map[(y * Target->w) + x];
			if( pxlLast.r != pxl.r || pxlLast.g != pxl.g || pxlLast.b != pxl.b )
			{
#ifdef PANDORA
				greyLast = (pxl.r >> 2) + (pxl.g >> 1) + (pxl.b >> 3);	// Faster but inaccurate
#else
				greyLast = ((float)pxl.r * 0.35f) + (pxl.g >> 1) + ((float)pxl.b * 0.15f);
#endif
			}
			map[(y * Target->w) + x].r = greyLast;
			map[(y * Target->w) + x].g = greyLast;
			map[(y * Target->w) + x].b = greyLast;
			pxlLast = pxl;
		}
	}

	SetARGBMap( Target, map );
}
