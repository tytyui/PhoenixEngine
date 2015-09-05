#ifndef PHOENIX_ASSERT_H
#define PHOENIX_ASSERT_H

#include <cassert>

namespace Phoenix
{

}

#define F_Assert(Expr, Msg) assert(Msg && Expr)

#endif
