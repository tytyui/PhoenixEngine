#ifndef PHOENIX_MATH_H
#define PHOENIX_MATH_H

#include <cmath>

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	template <class T>
	struct TMath
	{
		static T Abs(const T Value);
		static T Modulo(const T Value, const T Mod);
	};

	typedef TMath<Float32> FMathf;
	typedef TMath<Float64> FMathd;

	template <class T>
	T TMath<T>::Abs(const T Value)
	{
		const T Result = std::abs(Value);
		return Result;
	}

	template <class T>
	T TMath<T>::Modulo(const T Value, const T Mod)
	{
		const T Result = std::fmod(Value, Mod);
		return Result;
	}
}

#endif
