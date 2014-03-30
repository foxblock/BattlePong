
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
}
