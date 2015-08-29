#ifndef PHOENIX_LOG_H
#define PHOENIX_LOG_H

#include "Utility/Assert.h"
#include "Utility/FileStream.h"
#include "Utility/Mutex.h"
#include "Utility/Singleton.h"
#include "Utility/String.h"

namespace Phoenix
{
	class Log : public TSingleton<Log>
	{
		F_DeclareTSingleton(Log);
	public:
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
