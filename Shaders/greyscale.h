
#pragma once

#include "shader.h"

class ShaderGreyscale : public Shader
{
	private:

	public:
		ShaderGreyscale();
		~ShaderGreyscale();
		void Apply( SDL_Surface* Target );
};