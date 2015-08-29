#ifndef PHOENIX_PRIMITIVES_H
#define PHOENIX_PRIMITIVES_H

namespace Phoenix
{
	using FChar = char;

	using Int8 = signed char;
	using Int16 = signed short;
	using Int32 = signed int;
	using Int64 = signed long long;

	using UInt8 = unsigned char;
	using UInt16 = unsigned short;
	using UInt32 = unsigned int;
	using UInt64 = unsigned long long;

	using Float32 = float;
	using Float64 = double;

	using SizeT = size_t;
	using NullptrT = std::nullptr_t;

	enum class EInitParam
	{
		Null
	};
}

#endif
