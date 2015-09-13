#ifndef PHOENIX_PRIMITIVES_H
#define PHOENIX_PRIMITIVES_H

namespace Phoenix
{
	typedef char FChar;

	typedef signed char Int8;
	typedef signed short Int16;
	typedef signed int Int32;
	typedef signed long long Int64;

	typedef unsigned char UInt8;
	typedef unsigned short UInt16;
	typedef unsigned int UInt32;
	typedef unsigned long long UInt64;

	typedef float Float32;
	typedef double Float64;

	typedef size_t SizeT;

#if _WIN32
	typedef std::nullptr_t NullptrT;
#else
	typedef nullptr_t NullptrT;
#endif

	enum class EInitParam
	{
		Null
	};
}

#endif
