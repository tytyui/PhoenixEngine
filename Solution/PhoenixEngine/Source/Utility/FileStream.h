#ifndef PHOENIX_FILE_STREAM_H
#define PHOENIX_FILE_STREAM_H

#include <fstream>

namespace Phoenix
{
	using FFileStream = std::fstream;
	using FOutputFileStream = std::ofstream;
	using FInputFileStream = std::ifstream;
}

#endif
