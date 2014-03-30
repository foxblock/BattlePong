
#pragma once

#include "../Framework/graphicslib.h"

class ShaderBlur
{
	private:

	public:
		ShaderBlur();
		~ShaderBlur();
		void Apply( SDL_Surface* Target );
};