#ifndef PHOENIX_ASSERT_H
#define PHOENIX_ASSERT_H

#include <cassert>

#include "Utility/Misc/String.h"
#include "Utility/Misc/StringStream.h"

// #FIXME: Move to appropriate config file.
#define PHOENIX_ENABLE_ASSERT 1

#if PHOENIX_ENABLE_ASSERT
#	define F_Assert(Expr, Msg)					\
	{											\
		if (!(Expr))							\
		{										\
			FStringStream SS;					\
			SS << Msg;							\
			const FString StrMsg = SS.str();	\
												\
			assert(StrMsg.c_str() && (Expr));	\
		}										\
	}
#else
#	define F_Assert(Expr, Msg)
#endif

#define F_AssertEqual(Lhs, Rhs, Msg) F_Assert((Lhs == Rhs), Msg)
#define F_AssertNotEqual(Lhs, Rhs, Msg) F_Assert((Lhs != Rhs), Msg)
#define F_AssertIsNull(Expr, Msg) F_Assert((Expr == nullptr), Msg)
#define F_AssertNotNull(Expr, Msg) F_Assert((Expr != nullptr), Msg)
#define F_AssertTrue(Expr, Msg) F_Assert(Expr, Msg)
#define F_AssertFalse(Expr, Msg) F_Assert(!(Expr), Msg)

#if _WIN32
#	define F_Win32StaticAssert(Expr, Msg) static_assert(Expr, Msg)
#else
#	define F_Win32StaticAssert(Expr, Msg)
#endif

#endif
