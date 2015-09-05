#ifndef PHOENIX_STRING_H
#define PHOENIX_STRING_H

#include <string>

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	typedef std::string FString;

	namespace FStr // FIXME: Come up with a naming convention.
	{
		//	--------------------------------------------------------------------------------
		/*! \brief Extracts the file name from a file directory.
		*
		*	Input: Initial/Directory/AdditionalDirectory/SomeFile.cpp
		*	Output: SomeFile.cpp
		*/
		static inline FString ExtractFileName(const FString& FileDirectory)
		{
			static const FChar* const PathDelimiters = "/\\";

			const size_t Index = FileDirectory.find_last_of(PathDelimiters);

			if (Index == FString::npos)
			{
				return FileDirectory;
			}

			const FString FileName = FileDirectory.substr(Index + 1);
			return FileName;
		}
	}
}

#endif
