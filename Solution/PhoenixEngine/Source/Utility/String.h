#ifndef PHOENIX_STRING_H
#define PHOENIX_STRING_H

#include <string>

namespace Phoenix
{
	using FString = std::string;

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
			// FIXME: This should probably be a static const char* const.
			static const FString PathDelimiters = "/\\";

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
