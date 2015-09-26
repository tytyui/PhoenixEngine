#ifndef PHOENIX_STRING_H
#define PHOENIX_STRING_H

#include <cctype>
#include <string>

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	typedef std::string FString;

	namespace FStr // #FIXME: Come up with a naming convention.
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

		//	--------------------------------------------------------------------------------
		/*! \brief Extracts the file extension from a file or file directory.
		*
		*	Input: Initial/Directory/AdditionalDirectory/SomeFile.cpp
		*	Output: .cpp
		*/
		static inline FString ExtractExtension(const FString& File)
		{
			static const FChar* const ExtensionDelimiter = ".";

			const SizeT Index = File.find_last_of(ExtensionDelimiter);

			if (Index == FString::npos)
			{
				return "";
			}

			const FString Extension = File.substr(Index + 1);
			return Extension;
		}

		//	--------------------------------------------------------------------------------
		/*! \brief Converts any upper case characters to lower case.
		*
		*	Input: Initial/Directory/AdditionalDirectory/SomeFile.cpp
		*	Output: initial/directory/additionaldirectory/somefile.cpp
		*/
		static inline void ToLower(FString& String)
		{
			for (SizeT I = 0; I < String.size(); ++I)
			{
				String[I] = std::tolower(String[I]);
			}
		}
	}
}

#endif
