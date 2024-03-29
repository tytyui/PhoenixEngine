#ifndef PHOENIX_DEBUG_H
#define PHOENIX_DEBUG_H

#include <iomanip>
#include <iostream>

#include "Utility/Debug/ConsoleColor.h"
#include "Utility/Debug/Log.h"
#include "Utility/Misc/Singleton.h"
#include "Utility/Misc/StringStream.h"
#include "Utility/Threading/Mutex.h"

namespace Phoenix
{
	class Debug : public TSingleton<Debug>
	{
		F_DeclareTSingleton(Debug);
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

#define PHOENIX_DEBUG_LEVEL_0 0
#define PHOENIX_DEBUG_LEVEL_1 1
#define PHOENIX_DEBUG_LEVEL_2 2
#define PHOENIX_DEBUG_LEVEL_3 3
#define PHOENIX_DEBUG_CODE_ON 1
#define PHOENIX_DEBUG_BREAK_POINTS_ON 1

#define PHOENIX_DEBUG_LEVEL PHOENIX_DEBUG_LEVEL_3
#define PHOENIX_DEBUG_USE_CONSOLE 1
#define PHOENIX_DEBUG_THREAD_SAFE 1

#ifndef PHOENIX_DEBUG_CODE_ON
#	if _DEBUG
#		define PHOENIX_DEBUG_CODE_ON 1
#	else
#		define PHOENIX_DEBUG_CODE_ON 0
#	endif
#endif

#ifndef PHOENIX_DEBUG_BREAK_POINTS_ON
#	if _DEBUG
#		define PHOENIX_DEBUG_BREAK_POINTS_ON 1
#	else
#		define PHOENIX_DEBUG_BREAK_POINTS_ON 0
#	endif
#endif

#ifndef PHOENIX_DEBUG_LEVEL
#	if _DEBUG
#		define PHOENIX_DEBUG_LEVEL PHOENIX_DEBUG_LEVEL_3
#	else
#		define PHOENIX_DEBUG_LEVEL PHOENIX_DEBUG_LEVEL_0
#	endif
#endif

#ifndef PHOENIX_DEBUG_USE_CONSOLE
#	if _DEBUG
#		define PHOENIX_DEBUG_USE_CONSOLE 1
#	else
#		define PHOENIX_DEBUG_USE_CONSOLE 0
#	endif
#endif

#ifndef PHOENIX_DEBUG_THREAD_SAFE
#	if _DEBUG
#		define PHOENIX_DEBUG_THREAD_SAFE 1
#	else
#		define PHOENIX_DEBUG_THREAD_SAFE 1
#	endif
#endif

#if PHOENIX_DEBUG_BREAK_POINTS_ON
#	if _MSC_VER

#		define F_DebugBreak() DebugBreak()
#		define F_DebugBreakIf(Expr) if (Expr) { F_DebugBreak(); }

#		define F_DebugBreakOnce()					\
		{											\
			static bool DebugBreakFlag = true;		\
			if (DebugBreakFlag)						\
			{										\
				DebugBreakFlag = false;				\
				F_DebugBreak();						\
			}										\
		}

#		define F_DebugBreakOnceIf(Expr) if (Expr) { F_DebugBreakOnce(); }

#	endif
#endif

#if PHOENIX_DEBUG_CODE_ON
#	define F_DebugCode(Code) Code
#endif

#if PHOENIX_DEBUG_USE_CONSOLE

#	if PHOENIX_DEBUG_THREAD_SAFE
#		define PHOENIX_DEBUG_LOCK()	FMutexLock MutexLock(Debug::Get().GetLock());
#	else
#		define PHOENIX_DEBUG_LOCK()
#	endif

#	define F_LogOpen(File)

#	define F_LogClose()

#	define PHOENIX_DEBUG_INTERNAL(Color, PreMsg, Msg)	\
		{												\
			FStringStream SS;							\
			SS	<< PreMsg 								\
				<< NString::ExtractFileName(__FILE__)	\
				<< " @ "								\
				<< __LINE__								\
				<< ": "									\
				<< Msg									\
				<< '\n';								\
														\
			PHOENIX_DEBUG_LOCK();						\
			Debug::Get() 								\
				<< FConsoleColor(Color) 				\
				<< SS.str()								\
				<< FConsoleColor(EConsoleColor::Grey);	\
		}

#	if PHOENIX_DEBUG_LEVEL >= PHOENIX_DEBUG_LEVEL_1
#		define F_LogError(Msg)				PHOENIX_DEBUG_INTERNAL(EConsoleColor::Red, "..", Msg)
#		define F_LogErrorIf(Expr, Msg)		if (Expr) { F_LogError(Msg); }
#	endif

#	if PHOENIX_DEBUG_LEVEL >= PHOENIX_DEBUG_LEVEL_2
#		define F_LogWarning(Msg)			PHOENIX_DEBUG_INTERNAL(EConsoleColor::Yellow, "..", Msg)
#		define F_LogWarningIf(Expr, Msg)	if (Expr) { F_LogWarning(Msg); }
#	endif

#	if PHOENIX_DEBUG_LEVEL >= PHOENIX_DEBUG_LEVEL_3
#		define F_LogTrace(Msg)				PHOENIX_DEBUG_INTERNAL(EConsoleColor::White, "..", Msg)
#		define F_LogTraceIf(Expr, Msg)		if (Expr) { F_LogTrace(Msg); }
#	endif

#	if PHOENIX_DEBUG_LEVEL >= PHOENIX_DEBUG_LEVEL_3
#		define F_Log(Msg)					PHOENIX_DEBUG_INTERNAL(EConsoleColor::Grey, "..", Msg)
#		define F_LogIf(Expr, Msg)			if (Expr) { F_Log(Msg); }
#	endif

#else

#	if PHOENIX_DEBUG_THREAD_SAFE
#		define PHOENIX_DEBUG_LOCK()	FMutexLock MutexLock(Log::GetStaticObject().GetLock());
#	else
#		define PHOENIX_DEBUG_LOCK()
#	endif

#	if PHOENIX_DEBUG_LEVEL >= PHOENIX_DEBUG_LEVEL_1
#		define F_LogOpen(File)															\
			{																			\
				PHOENIX_DEBUG_LOCK();													\
				Log::GetStaticObject().Init(File);										\
				F_Assert(Log::GetStaticObject().IsValid(), "Failed to open file.");		\
			}

#		define F_LogClose()																\
			{																			\
				PHOENIX_DEBUG_LOCK();													\
				Log::GetStaticObject().DeInit();										\
			}
#	endif

#	define PHOENIX_DEBUG_INTERNAL(PreMsg, Msg)			\
		{												\
			FStringStream SS;							\
			SS	<< PreMsg 								\
				<< NString::ExtractFileName(__FILE__)	\
				<< " @ "								\
				<< __LINE__								\
				<< ": "									\
				<< Msg									\
				<< '\n';								\
														\
			PHOENIX_DEBUG_LOCK();						\
			Log::GetStaticObject() << SS.str();			\
		}

#	if PHOENIX_DEBUG_LEVEL >= PHOENIX_DEBUG_LEVEL_1
#		define F_LogError(Msg)				PHOENIX_DEBUG_INTERNAL("Error: ..", Msg)
#		define F_LogErrorIf(Expr, Msg)		if (Expr) { F_LogError(Msg); }
#	endif

#	if PHOENIX_DEBUG_LEVEL >= PHOENIX_DEBUG_LEVEL_2
#		define F_LogWarning(Msg)			PHOENIX_DEBUG_INTERNAL("Warning: ..", Msg)
#		define F_LogWarningIf(Expr, Msg)	if (Expr) { F_LogWarning(Msg); }
#	endif

#	if PHOENIX_DEBUG_LEVEL >= PHOENIX_DEBUG_LEVEL_3
#		define F_LogTrace(Msg)				PHOENIX_DEBUG_INTERNAL("Trace: ..", Msg)
#		define F_LogTraceIf(Expr, Msg)		if (Expr) { F_LogTrace(Msg); }
#	endif

#	if PHOENIX_DEBUG_LEVEL >= PHOENIX_DEBUG_LEVEL_3
#		define F_Log(Msg)					PHOENIX_DEBUG_INTERNAL("Misc: ..", Msg)
#		define F_LogIf(Expr, Msg)			if (Expr) { F_Log(Msg); }
#	endif

#endif

#ifndef F_DebugBreak
#	define F_DebugBreak()
#endif

#ifndef F_DebugBreakIf
#	define F_DebugBreakIf(Expr)
#endif

#ifndef F_DebugBreakOnce
#	define F_DebugBreakOnce()
#endif

#ifndef F_DebugBreakOnceIf
#	define F_DebugBreakOnceIf(Expr)
#endif

#ifndef F_DebugCode
#	define F_DebugCode(Code)
#endif

#ifndef F_LogOpen
#	define F_LogOpen(File)
#endif

#ifndef F_LogClose
#	define F_LogClose()
#endif

#ifndef F_LogError
#	define F_LogError(Msg)
#endif

#ifndef F_LogErrorIf
#	define F_LogErrorIf(Expr, Msg)
#endif

#ifndef F_LogWarning
#	define F_LogWarning(Msg)
#endif

#ifndef F_LogWarningIf
#	define F_LogWarningIf(Expr, Msg)
#endif

#ifndef F_LogTrace
#	define F_LogTrace(Msg)
#endif

#ifndef F_LogTraceIf
#	define F_LogTraceIf(Expr, Msg)
#endif

#ifndef F_Log
#	define F_Log(Msg)
#endif

#ifndef F_LogIf
#	define F_LogIf(Expr, Msg)
#endif

#endif
