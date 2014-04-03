
#pragma once

#include "shader.h"

class ShaderScanlines : public Shader
{
	private:
		int nonScanLineWidth;
		int scanLineWidth;
		int scanDecrease;

	public:
		ShaderScanlines();
		ShaderScanlines(int NonScanWidth, int ScanWidth, int ScanDecrease);
		~ShaderScanlines();
		void Apply( SDL_Surface* Target );
};