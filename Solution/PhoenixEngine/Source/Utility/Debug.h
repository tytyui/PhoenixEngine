#ifndef F_PHOENIX_DEBUG_H
#define F_PHOENIX_DEBUG_H

#include <iomanip>
#include <iostream>

#include "Utility/ConsoleColor.h"
#include "Utility/Log.h"
#include "Utility/Mutex.h"
#include "Utility/Singleton.h"
#include "Utility/StringStream.h"

namespace Phoenix
{
	class Debug : public TSingleton<Debug>
	{
		F_DECLARE_TSINGLETON(Debug);
	public:
		FMutex& GetLock();

		template <class T>
		Debug& operator<<(const T& Data);

	protected:
	private:
		FMutex Lock;
	};

	inline FMutex& Debug::GetLock()
	{
		return Lock;
	}

	template <class T>
	Debug& Debug::operator<<(const T& Data)
	{
		std::cout << Data;
		return *this;
	}

	template <>
	inline Debug& Debug::operator<<(const FConsoleColor& Data)
	{
		FConsoleColor::Set(Data);
		return *this;
	}
}

#define F_DEBUG_LEVEL_0 0
#define F_DEBUG_LEVEL_1 1
#define F_DEBUG_LEVEL_2 2
#define F_DEBUG_LEVEL_3 3

#define F_DEBUG_LEVEL F_DEBUG_LEVEL_3
#define F_DEBUG_USE_CONSOLE 1
#define F_DEBUG_THREAD_SAFE 1

#ifndef F_DEBUG_LEVEL
#	if _DEBUG
#		define F_DEBUG_LEVEL F_DEBUG_LEVEL_3
#	else
#		define F_DEBUG_LEVEL F_DEBUG_LEVEL_0
#	endif
#endif

#ifndef F_DEBUG_USE_CONSOLE
#	if _DEBUG
#		define F_DEBUG_USE_CONSOLE 1
#	else
#		define F_DEBUG_USE_CONSOLE 0
#	endif
#endif

#ifndef F_DEBUG_THREAD_SAFE
#	if _DEBUG
#		define F_DEBUG_THREAD_SAFE 1
#	else
#		define F_DEBUG_THREAD_SAFE 1
#	endif
#endif

#if F_DEBUG_USE_CONSOLE

#	if F_DEBUG_THREAD_SAFE
#		define F_DEBUG_LOCK()	FMutexLock MutexLock(Debug::Get().GetLock());
#	else
#		define F_DEBUG_LOCK()
#	endif

#	define F_LOG_OPEN(File)

#	define F_LOG_CLOSE()

#	define F_DEBUG_INTERNAL(Color, PreMsg, Msg)		\
		{											\
			FStringStream SS;						\
			SS	<< PreMsg 							\
				<< FStr::ExtractFileName(__FILE__)	\
				<< " @ "							\
				<< __LINE__							\
				<< ": "								\
				<< Msg								\
				<< '\n';							\
													\
			F_DEBUG_LOCK();							\
			Debug::Get() 							\
				<< FConsoleColor(Color) 			\
				<< SS.str();						\
		}

#	if F_DEBUG_LEVEL >= F_DEBUG_LEVEL_1
#		define F_LOG_ERROR(Msg)		F_DEBUG_INTERNAL(EConsoleColor::Red, "..", Msg)
#	endif

#	if F_DEBUG_LEVEL >= F_DEBUG_LEVEL_2
#		define F_LOG_WARNING(Msg)	F_DEBUG_INTERNAL(EConsoleColor::Yellow, "..", Msg)
#	endif

#	if F_DEBUG_LEVEL >= F_DEBUG_LEVEL_3
#		define F_LOG_TRACE(Msg)		F_DEBUG_INTERNAL(EConsoleColor::White, "..", Msg)
#	endif

#	if F_DEBUG_LEVEL >= F_DEBUG_LEVEL_3
#		define F_LOG(Msg)			F_DEBUG_INTERNAL(EConsoleColor::Grey, "..", Msg)
#	endif

#else

#	if F_DEBUG_THREAD_SAFE
#		define F_DEBUG_LOCK()	FMutexLock MutexLock(Log::Get().GetLock());
#	else
#		define F_DEBUG_LOCK()
#	endif

#	if F_DEBUG_LEVEL >= F_DEBUG_LEVEL_1
#		define F_LOG_OPEN(File)												\
			{																\
				F_DEBUG_LOCK();												\
				Log::Get().Init(File);										\
				F_ASSERT(Log::Get().IsValid(), "Failed to open file.");		\
			}

#		define F_LOG_CLOSE()												\
			{																\
				F_DEBUG_LOCK();												\
				Log::Get().DeInit();										\
			}
#	endif

#	define F_DEBUG_INTERNAL(PreMsg, Msg)			\
		{											\
			FStringStream SS;						\
			SS	<< PreMsg 							\
				<< FStr::ExtractFileName(__FILE__)	\
				<< " @ "							\
				<< __LINE__							\
				<< ": "								\
				<< Msg								\
				<< '\n';							\
													\
			F_DEBUG_LOCK();							\
			Log::Get() 								\
				<< SS.str();						\
		}

#	if F_DEBUG_LEVEL >= F_DEBUG_LEVEL_1
#		define F_LOG_ERROR(Msg)		F_DEBUG_INTERNAL("Error: ..", Msg)
#	endif

#	if F_DEBUG_LEVEL >= F_DEBUG_LEVEL_2
#		define F_LOG_WARNING(Msg)	F_DEBUG_INTERNAL("Warning: ..", Msg)
#	endif

#	if F_DEBUG_LEVEL >= F_DEBUG_LEVEL_3
#		define F_LOG_TRACE(Msg)		F_DEBUG_INTERNAL("Trace: ..", Msg)
#	endif

#	if F_DEBUG_LEVEL >= F_DEBUG_LEVEL_3
#		define F_LOG(Msg)			F_DEBUG_INTERNAL("Misc: ..", Msg)
#	endif

#endif

#ifndef F_LOG_OPEN
#	define F_LOG_OPEN(File)
#endif

#ifndef F_LOG_CLOSE
#	define F_LOG_CLOSE()
#endif

#ifndef F_LOG_ERROR
#	define F_LOG_ERROR(Msg)
#endif

#ifndef F_LOG_WARNING
#	define F_LOG_WARNING(Msg)
#endif

#ifndef F_LOG_TRACE
#	define F_LOG_TRACE(Msg)
#endif

#ifndef F_LOG
#	define F_LOG(Msg)
#endif

#endif
