#ifndef PHOENIX_PRIMITIVES_H
#define PHOENIX_PRIMITIVES_H

namespace Phoenix
{
	using FChar = char;

	using SI8 = signed char;
	using SI16 = signed short;
	using SI32 = signed int;
	using SI64 = signed long long;

	using UI8 = unsigned char;
	using UI16 = unsigned short;
	using UI32 = unsigned int;
	using UI64 = unsigned long long;

	using F32 = float;
	using F64 = double;

	using SizeT = size_t;
	using NullptrT = std::nullptr_t;

	enum class EInitParam
	{
		Null
	};
}

#endif
