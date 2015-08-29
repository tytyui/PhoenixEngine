#ifndef PHOENIX_ENDIAN_H
#define PHOENIX_ENDIAN_H

#include "Utility/Primitives.h"

namespace Phoenix
{
	class FEndian
	{
	public:
		FEndian() = delete;
		FEndian(const FEndian&) = delete;
		FEndian(FEndian&&) = delete;
		FEndian& operator=(const FEndian&) = delete;
		FEndian& operator=(FEndian&&) = delete;

		static void Init();

		template <class T>
		static T SwapLE(const T LEData);

		template <class T>
		static T SwapBE(const T BEData);

	protected:
	private:
		template <class T>
		using TSwapFunc = T(*)(const T);

		static TSwapFunc<SI16> SwapLittleSI16;
		static TSwapFunc<SI32> SwapLittleSI32;
		static TSwapFunc<UI16> SwapLittleUI16;
		static TSwapFunc<UI32> SwapLittleUI32;
		static TSwapFunc<F32> SwapLittleF32;

		static TSwapFunc<SI16> SwapBigSI16;
		static TSwapFunc<SI32> SwapBigSI32;
		static TSwapFunc<UI16> SwapBigUI16;
		static TSwapFunc<UI32> SwapBigUI32;
		static TSwapFunc<F32> SwapBigF32;

		template <class T>
		static T InternalSwap(const T Data);

		template <>
		static SI16 InternalSwap(const SI16 Data);

		template <>
		static SI32 InternalSwap(const SI32 Data);

		template <>
		static UI16 InternalSwap(const UI16 Data);

		template <>
		static UI32 InternalSwap(const UI32 Data);

		template <>
		static F32 InternalSwap(const F32 Data);

		template <class T>
		static T InternalNoSwap(const T Data);
	};

	inline void FEndian::Init()
	{
		union
		{
			UI32 Byte4;
			UI8 Byte1;
		} EndianTest;

		EndianTest.Byte4 = 0x01;
		const bool bIsLittleEndian = EndianTest.Byte1 == 1;

		if (bIsLittleEndian)
		{
			// FIXME: LOG("Little endian system detected.");
			FEndian::SwapLittleSI16 = &FEndian::InternalNoSwap<SI16>;
			FEndian::SwapLittleSI32 = &FEndian::InternalNoSwap<SI32>;
			FEndian::SwapLittleUI16 = &FEndian::InternalNoSwap<UI16>;
			FEndian::SwapLittleUI32 = &FEndian::InternalNoSwap<UI32>;
			FEndian::SwapLittleF32 = &FEndian::InternalNoSwap<F32>;

			FEndian::SwapBigSI16 = &FEndian::InternalSwap<SI16>;
			FEndian::SwapBigSI32 = &FEndian::InternalSwap<SI32>;
			FEndian::SwapBigUI16 = &FEndian::InternalSwap<UI16>;
			FEndian::SwapBigUI32 = &FEndian::InternalSwap<UI32>;
			FEndian::SwapBigF32 = &FEndian::InternalSwap<F32>;
		}
		else
		{
			// FIXME: LOG("Big endian system detected.");
			FEndian::SwapLittleSI16 = &FEndian::InternalSwap<SI16>;
			FEndian::SwapLittleSI32 = &FEndian::InternalSwap<SI32>;
			FEndian::SwapLittleUI16 = &FEndian::InternalSwap<UI16>;
			FEndian::SwapLittleUI32 = &FEndian::InternalSwap<UI32>;
			FEndian::SwapLittleF32 = &FEndian::InternalSwap<F32>;

			FEndian::SwapBigSI16 = &FEndian::InternalNoSwap<SI16>;
			FEndian::SwapBigSI32 = &FEndian::InternalNoSwap<SI32>;
			FEndian::SwapBigUI16 = &FEndian::InternalNoSwap<UI16>;
			FEndian::SwapBigUI32 = &FEndian::InternalNoSwap<UI32>;
			FEndian::SwapBigF32 = &FEndian::InternalNoSwap<F32>;
		}
	}

	template <class T>
	T FEndian::SwapLE(const T LEData)
	{
		static_assert(false, "This function must be specialized.");
	}

	template <class T>
	T FEndian::SwapBE(const T BEData)
	{
		static_assert(false, "This function must be specialized.");
	}

	template <>
	inline SI16 FEndian::SwapLE(const SI16 LEData)
	{
		// FIXME: ASSERT(FEndian::SwapLittleSI16, "Endian::SwapLittleSI16 is null.");
		return FEndian::SwapLittleSI16(LEData);
	}

	template <>
	inline SI32 FEndian::SwapLE(const SI32 LEData)
	{
		// FIXME: ASSERT(FEndian::SwapLittleSI32, "Endian::SwapLittleSI32 is null.");
		return FEndian::SwapLittleSI32(LEData);
	}

	template <>
	inline UI16 FEndian::SwapLE(const UI16 LEData)
	{
		// FIXME: ASSERT(FEndian::SwapLittleUI16, "Endian::SwapLittleUI16 is null.");
		return FEndian::SwapLittleUI16(LEData);
	}

	template <>
	inline UI32 FEndian::SwapLE(const UI32 LEData)
	{
		// FIXME: ASSERT(FEndian::SwapLittleUI32, "Endian::SwapLittleUI32 is null.");
		return FEndian::SwapLittleUI32(LEData);
	}

	template <>
	inline SI16 FEndian::SwapBE(const SI16 BEData)
	{
		// FIXME: ASSERT(FEndian::SwapBigSI16, "Endian::SwapBigSI16 is null.");
		return FEndian::SwapBigSI16(BEData);
	}

	template <>
	inline SI32 FEndian::SwapBE(const SI32 BEData)
	{
		// FIXME: ASSERT(FEndian::SwapBigSI32, "Endian::SwapBigSI32 is null.");
		return FEndian::SwapBigSI32(BEData);
	}

	template <>
	inline UI16 FEndian::SwapBE(const UI16 BEData)
	{
		// FIXME: ASSERT(FEndian::SwapBigUI16, "Endian::SwapBigUI16 is null.");
		return FEndian::SwapBigUI16(BEData);
	}

	template <>
	inline UI32 FEndian::SwapBE(const UI32 BEData)
	{
		// FIXME: ASSERT(FEndian::SwapBigUI32, "Endian::SwapBigUI32 is null.");
		return FEndian::SwapBigUI32(BEData);
	}

	template <class T>
	T FEndian::InternalSwap(const T Data)
	{
		static_assert(false, "This function must be specialized.");
	}

	template <>
	inline SI16 FEndian::InternalSwap(const SI16 Data)
	{
		const UI16* const UI16Ptr = reinterpret_cast<const UI16*>(&Data);
		const UI16 UI16Result = FEndian::InternalSwap(*UI16Ptr);
		const SI16* const SI16Ptr = reinterpret_cast<const SI16*>(&UI16Result);
		const SI16 Result = *SI16Ptr;
		return Result;
	}

	template <>
	inline SI32 FEndian::InternalSwap(const SI32 Data)
	{
		const UI32* const UI32Ptr = reinterpret_cast<const UI32*>(&Data);
		const UI32 UI32Result = FEndian::InternalSwap(*UI32Ptr);
		const SI32* const SI32Ptr = reinterpret_cast<const SI32*>(&UI32Result);
		const SI32 Result = *SI32Ptr;
		return Result;
	}

	template <>
	inline UI16 FEndian::InternalSwap(const UI16 Data)
	{
		const UI16 Result =
			((Data >> 8) & 0x00FF) +
			((Data << 8) & 0xFF00);
		return Result;
	}

	template <>
	inline UI32 FEndian::InternalSwap(const UI32 Data)
	{
		const UI32 Result =
			((Data >> 24) & 0x000000FF) +
			((Data >> 8) & 0x0000FF00) +
			((Data << 8) & 0x00FF0000) +
			((Data << 24) & 0xFF000000);
		return Result;
	}

	template <>
	inline F32 FEndian::InternalSwap(const F32 Data)
	{
		static_assert(sizeof(UI32) == sizeof(F32), "UI32 size does not equal F32 size.");
		union
		{
			UI32 UI32Data;
			F32 F32Data;
		} FloatSwap;

		FloatSwap.F32Data = Data;
		FloatSwap.UI32Data = FEndian::InternalSwap(FloatSwap.UI32Data);

		return FloatSwap.F32Data;
	}

	template <class T>
	T FEndian::InternalNoSwap(const T Data)
	{
		return Data;
	}
}

#endif
