#include "scanlines.h"

ShaderScanlines::ShaderScanlines()
{
	nonScanLineWidth = 4;
	scanLineWidth = 2;
	scanDecrease = 32;
}

ShaderScanlines::ShaderScanlines(int NonScanWidth, int ScanWidth, int ScanDecrease)
{
	nonScanLineWidth = NonScanWidth;
	scanLineWidth = ScanWidth;
	scanDecrease = ScanDecrease;
}

ShaderScanlines::~ShaderScanlines()
{
}

void ShaderScanlines::Apply( SDL_Surface* Target )
{
	ShaderARBG* map = GetARGBMap( Target );
	int linesForScan = nonScanLineWidth + scanLineWidth;

	for( int y = 0; y < Target->h; y++ )
	{
		if( (y % linesForScan) >= nonScanLineWidth )
		{
			for( int x = 0; x < Target->w; x++ )
			{
				ShaderARBG pxl = map[(y * Target->w) + x];
				map[(y * Target->w) + x].r = (pxl.r > scanDecrease ? pxl.r - scanDecrease : 0);
				map[(y * Target->w) + x].g = (pxl.g > scanDecrease ? pxl.g - scanDecrease : 0);
				map[(y * Target->w) + x].b = (pxl.b > scanDecrease ? pxl.b - scanDecrease : 0);
			}
		}
	}

	SetARGBMap( Target, map );
}
