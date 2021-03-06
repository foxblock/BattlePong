
#pragma once

#include "../Framework/graphicslib.h"

typedef struct {
	Uint8 b;
	Uint8 g;
	Uint8 r;
	Uint8 a;
} ShaderARBG;

class Shader
{
	private:
		SDL_PixelFormat genericFormat;

	protected:
		ShaderARBG* GetARGBMap( SDL_Surface* surface );
		void SetARGBMap( SDL_Surface* surface, ShaderARBG* argbmap );

	public:
		Shader();
		virtual void Apply( SDL_Surface* Target ) = 0;
};