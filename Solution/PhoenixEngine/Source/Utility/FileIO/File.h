#ifndef __SPATTERFILE_H__
#define __SPATTERFILE_H__

#include "Utility/Misc/FileStream.h"
#include "Utility/Misc/Memory.h"
#include "Utility/Misc/String.h"
#include "Utility/Misc/StringStream.h"

namespace Phoenix
{
	class FFile
	{

	public:

		struct EFileOpenMode
		{
			enum Value : std::ios_base::openmode
			{
				Closed = -1,
				Append = std::ios_base::app,
				AtEnd = std::ios_base::ate,
				Binary = std::ios_base::binary,
				Read = std::ios_base::in,
				Write = std::ios_base::out,
				Truncate = std::ios_base::trunc
			};
		};

		FFile(const FString& InFilePath);

	private:

		FFile() = delete;

		EFileOpenMode::Value OpenState { EFileOpenMode::Value::Closed };

		FFileStream FileStream;

		FString FilePath;

		FString Data;

		bool bIsOpen;

	public:

		bool Open(EFileOpenMode::Value FileOpenMode);

		void Close();

		void Read();

		// Simply 'resets' the file
		void Overwrite();

		// Overwrites with content of Data
		template <typename T>
		void Phoenix::FFile::Overwrite(const T& Data)
		{
			if (bIsOpen)
			{
				FileStream << Data;
			}
			else
			{
				// Error
			}
		}

		// Check for if the file has nothing in it, or didn't load properly
		bool Empty() const;

		// Appends
		template <typename T>
		void Phoenix::FFile::Write(const T& Data)
		{
			if (bIsOpen)
			{
				FileStream << Data;
			}
			else
			{
				// Error
			}
		}

		const FString& Content() const;

		template <typename T>
		inline void operator<<(const T& Data)
		{
			Write(Data);
		}

	protected:
		
	};
}

#endif