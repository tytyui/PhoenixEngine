#include "Utility/FileIO//File.h"

Phoenix::FFile::FFile(const FString& InFilePath)
{
	FilePath = InFilePath;
	bIsOpen = false;

	Read();
}

bool Phoenix::FFile::Open(EFileOpenMode::Value FileOpenMode)
{
	if (bIsOpen)
	{
		Close();
	}

	FileStream.open(FilePath.c_str(), FileOpenMode);

	bIsOpen = FileStream.is_open();
	if (!bIsOpen)
	{
		//TODO::Log error
		return false;
	}

	OpenState = FileOpenMode;

	return true;
}

void Phoenix::FFile::Close()
{
	if (bIsOpen)
	{
		FileStream.close();
		bIsOpen = FileStream.is_open();

		if (!bIsOpen)
		{
			OpenState = EFileOpenMode::Value::Closed;
		}
	}
}

void Phoenix::FFile::Read()
{
	Open(EFileOpenMode::Value::Read);

	if (bIsOpen)
	{
		FStringStream StringStream;
		StringStream << FileStream.rdbuf();
		Data = StringStream.str();
	}
}

bool Phoenix::FFile::Empty() const
{
	return Data.empty();
}

void Phoenix::FFile::Overwrite()
{
	if (bIsOpen)
	{
		Close();
		Open(EFileOpenMode::Write);
	}
	else
	{
		// Error
	}
}

const Phoenix::FString& Phoenix::FFile::Content() const
{
	return Data;
}
