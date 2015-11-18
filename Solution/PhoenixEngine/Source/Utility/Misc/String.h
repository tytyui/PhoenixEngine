#ifndef PHOENIX_STRING_H
#define PHOENIX_STRING_H

#include <cctype>
#include <string>

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	typedef std::string FString;

	namespace NString
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
		/*! \brief Finds the index in Str of the last character(s) specified in Contents.
		*
		*	Input: "Initial/File.cpp" 17 "/\\"
		*	Output: 7.  FString::npos is returned if nothing was found.
		*	Note: All FChar* must be null terminated.
		*/
		static inline SizeT FindLastOf(
			const FChar* const Str,
			const SizeT StrLength,
			const FChar* const Contents)
		{
			const bool StrIsInvalid = Str == nullptr || StrLength == 0 || Str[0] == '\0';
			const bool ContentsAreInvalid = Contents == nullptr || Contents[0] == '\0';

			if (StrIsInvalid || ContentsAreInvalid)
			{
				return FString::npos;
			}

			const SizeT ContentsLength = std::strlen(Contents);

			for (SizeT I = StrLength - 1; ; --I)
			{
				for (SizeT J = 0; J < ContentsLength; ++J)
				{
					if (Str[I] == Contents[J])
					{
						return I;
					}
				}

				if (I == 0)
				{
					break;
				}
			}

			return FString::npos;
		}

		//	--------------------------------------------------------------------------------
		/*! \brief Calculates the length of the string.
		*
		*	Input: SomeString.txt
		*	Output: 14
		*/
		static SizeT GetLength(const FChar* const Str)
		{
			const SizeT Length = std::strlen(Str);
			return Length;
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
