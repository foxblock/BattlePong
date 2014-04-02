
#pragma once

#include "shader.h"

class ShaderBlur : public Shader
{
	private:

	public:
		ShaderBlur();
		~ShaderBlur();
		void Apply( SDL_Surface* Target );
};