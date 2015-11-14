#ifndef PHOENIX_LOG_H
#define PHOENIX_LOG_H

#include "Utility/Debug/Assert.h"
#include "Utility/FileIO/FileStream.h"
#include "Utility/Misc/StaticObject.h"
#include "Utility/Misc/String.h"
#include "Utility/Threading/Mutex.h"

namespace Phoenix
{
	class Log
	{
		F_AddStaticObjectToClass(Log);
	public:
		Log() = default;

		Log(const Log&) = delete;
		Log& operator=(const Log&) = delete;

		Log(Log&&) = delete;
		Log& operator=(Log&&) = delete;

		~Log();

		void Init(const FString& File);

		bool IsValid() const;

		void DeInit();

		FMutex& GetLock();

		template <class T>
		Log& operator<<(const T& Data);

	protected:
	private:
		FOutputFileStream OFStream;
		FMutex Lock;
	};

	inline Log::~Log()
	{
		DeInit();
	}

	inline void Log::Init(const FString& File)
	{
		DeInit();
		OFStream.open(File, std::ios_base::out | std::ios_base::trunc);
	}

	inline bool Log::IsValid() const
	{
		const bool bIsValid = OFStream.is_open();
		return bIsValid;
	}

	inline void Log::DeInit()
	{
		if (OFStream.is_open())
		{
			OFStream.close();
		}
	}

	inline FMutex& Log::GetLock()
	{
		return Lock;
	}

	template <class T>
	Log& Log::operator<<(const T& Data)
	{
		F_Assert(IsValid(), "This class must be valid.");
		OFStream << Data;
		return *this;
	}

	template <>
	inline Log& Log::operator<<(const FConsoleColor& Data)
	{
		F_Assert(IsValid(), "This class must be valid.");
		return *this;
	}
}

#endif
