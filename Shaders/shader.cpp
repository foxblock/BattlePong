
#include "blur.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

void Shader::Apply( SDL_Surface* Target )
{
}


Uint32 Shader::GetPixel32(SDL_Surface* surface, int x, int y)
{
    Uint8 * pixel = (Uint8*)surface->pixels;
    pixel += (y * surface->pitch) + (x * sizeof(Uint32));
    return *((Uint32*)pixel);
}

Uint32 Shader::GetPixel24(SDL_Surface* surface, int x, int y)
{
    Uint8 * pixel = (Uint8*)surface->pixels;
    pixel += (y * surface->pitch) + (x * sizeof(Uint8) * 3);
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    //pixel[0] = (color >> 24) & 0xFF;
    //pixel[1] = (color >> 16) & 0xFF;
    //pixel[2] = (color >> 8) & 0xFF;
		return (Uint32)( (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | 0xFF )
#else
    //pixel[0] = color & 0xFF;
    //pixel[1] = (color >> 8) & 0xFF;
    //pixel[2] = (color >> 16) & 0xFF;
		return (Uint32)( pixel[0] | (pixel[1] << 8) | (pixel[2] << 16) | 0xFF000000 )
#endif
}

Uint32 Shader::GetPixel16(SDL_Surface* surface, int x, int y)
{
    Uint8 * pixel = (Uint8*)surface->pixels;
    pixel += (y * surface->pitch) + (x * sizeof(Uint16));
    Uint16 px = *((Uint16*)pixel);
		return (Uint32)px;
}

void Shader::SetPixel32(SDL_Surface* surface, int x, int y, Uint32 color)
{
    Uint8 * pixel = (Uint8*)surface->pixels;
    pixel += (y * surface->pitch) + (x * sizeof(Uint32));
    *((Uint32*)pixel) = color;
}

void Shader::SetPixel24(SDL_Surface* surface, int x, int y, Uint32 color)
{
    Uint8 * pixel = (Uint8*)surface->pixels;
    pixel += (y * surface->pitch) + (x * sizeof(Uint8) * 3);
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    pixel[0] = (color >> 24) & 0xFF;
    pixel[1] = (color >> 16) & 0xFF;
    pixel[2] = (color >> 8) & 0xFF;
#else
    pixel[0] = color & 0xFF;
    pixel[1] = (color >> 8) & 0xFF;
    pixel[2] = (color >> 16) & 0xFF;
#endif
}

void Shader::SetPixel16(SDL_Surface* surface, int x, int y, Uint32 color)
{
    Uint8 * pixel = (Uint8*)surface->pixels;
    pixel += (y * surface->pitch) + (x * sizeof(Uint16));
    *((Uint16*)pixel) = color & 0xFFFF;
}

Uint32 Shader::GetPixel( SDL_Surface* surface, int x, int y )
{
	switch( surface->format->BitsPerPixel )
	{
		case 16:
			return GetPixel16( surface, x, y );
			break;
		case 24:
			return GetPixel24( surface, x, y );
			break;
		case 32:
			return GetPixel32( surface, x, y );
			break;
	}
}

void Shader::SetPixel( SDL_Surface* surface, int x, int y, Uint32 color )
{
	switch( surface->format->BitsPerPixel )
	{
		case 16:
			SetPixel16( surface, x, y, color );
			break;
		case 24:
			SetPixel24( surface, x, y, color );
			break;
		case 32:
			SetPixel32( surface, x, y, color );
			break;
	}
}

