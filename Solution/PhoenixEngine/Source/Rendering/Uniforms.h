#ifndef PHOENIX_UNIFORMS_H
#define PHOENIX_UNIFORMS_H

#include "ExternalLib/GLIncludes.h"

namespace Phoenix
{
	namespace EUniform
	{
		/* Matrices */
		static const GLchar* const Projection = "uProjection";
		static const GLchar* const View = "uView";
		static const GLchar* const World = "uWorld";

		/* Textures */
		static const GLchar* const DiffuseMap = "uDiffuseMap";
		static const GLchar* const NormalMap = "uNormalMap";
	}
}

#endif
