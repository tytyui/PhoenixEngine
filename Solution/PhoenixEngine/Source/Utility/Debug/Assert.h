#ifndef PHOENIX_ASSERT_H
#define PHOENIX_ASSERT_H

#include <cassert>

namespace Phoenix
{

}

#define F_Assert(Expr, Msg) assert(Msg && Expr)

#if _WIN32
#	define F_Win32StaticAssert(Expr, Msg) static_assert(Expr, Msg)
#else
#	define F_Win32StaticAssert(Expr, Msg)
#endif

#endif
