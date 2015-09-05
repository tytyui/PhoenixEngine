#ifndef PHOENIX_ENDIAN_H
#define PHOENIX_ENDIAN_H

#include "Utility/Debug/Assert.h"
#include "Utility/Debug/Debug.h"
#include "Utility/Misc/Primitives.h"

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

		static TSwapFunc<Int16> SwapLittleInt16;
		static TSwapFunc<Int32> SwapLittleInt32;
		static TSwapFunc<UInt16> SwapLittleUInt16;
		static TSwapFunc<UInt32> SwapLittleUInt32;
		static TSwapFunc<Float32> SwapLittleFloat32;

		static TSwapFunc<Int16> SwapBigInt16;
		static TSwapFunc<Int32> SwapBigInt32;
		static TSwapFunc<UInt16> SwapBigUInt16;
		static TSwapFunc<UInt32> SwapBigUInt32;
		static TSwapFunc<Float32> SwapBigFloat32;

		template <class T>
		static T InternalSwap(const T Data);

		template <>
		static Int16 InternalSwap(const Int16 Data);

		template <>
		static Int32 InternalSwap(const Int32 Data);

		template <>
		static UInt16 InternalSwap(const UInt16 Data);

		template <>
		static UInt32 InternalSwap(const UInt32 Data);

		template <>
		static Float32 InternalSwap(const Float32 Data);

		template <class T>
		static T InternalSwap16(const T Data16);

		template <class T>
		static T InternalSwap32(const T Data32);

		template <class T>
		static T InternalNoSwap(const T Data);
	};

	inline void FEndian::Init()
	{
		union
		{
			UInt32 Byte4;
			UInt8 Byte1;
		} EndianTest;

		EndianTest.Byte4 = 0x01;
		const bool bIsLittleEndian = EndianTest.Byte1 == 0x01;

		if (bIsLittleEndian)
		{
			F_Log("Little endian system detected.");
			FEndian::SwapLittleInt16 = &FEndian::InternalNoSwap<Int16>;
			FEndian::SwapLittleInt32 = &FEndian::InternalNoSwap<Int32>;
			FEndian::SwapLittleUInt16 = &FEndian::InternalNoSwap<UInt16>;
			FEndian::SwapLittleUInt32 = &FEndian::InternalNoSwap<UInt32>;
			FEndian::SwapLittleFloat32 = &FEndian::InternalNoSwap<Float32>;

			FEndian::SwapBigInt16 = &FEndian::InternalSwap<Int16>;
			FEndian::SwapBigInt32 = &FEndian::InternalSwap<Int32>;
			FEndian::SwapBigUInt16 = &FEndian::InternalSwap<UInt16>;
			FEndian::SwapBigUInt32 = &FEndian::InternalSwap<UInt32>;
			FEndian::SwapBigFloat32 = &FEndian::InternalSwap<Float32>;
		}
		else
		{
			F_Log("Big endian system detected.");
			FEndian::SwapLittleInt16 = &FEndian::InternalSwap<Int16>;
			FEndian::SwapLittleInt32 = &FEndian::InternalSwap<Int32>;
			FEndian::SwapLittleUInt16 = &FEndian::InternalSwap<UInt16>;
			FEndian::SwapLittleUInt32 = &FEndian::InternalSwap<UInt32>;
			FEndian::SwapLittleFloat32 = &FEndian::InternalSwap<Float32>;

			FEndian::SwapBigInt16 = &FEndian::InternalNoSwap<Int16>;
			FEndian::SwapBigInt32 = &FEndian::InternalNoSwap<Int32>;
			FEndian::SwapBigUInt16 = &FEndian::InternalNoSwap<UInt16>;
			FEndian::SwapBigUInt32 = &FEndian::InternalNoSwap<UInt32>;
			FEndian::SwapBigFloat32 = &FEndian::InternalNoSwap<Float32>;
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
	inline Int16 FEndian::SwapLE(const Int16 LEData)
	{
		F_Assert(FEndian::SwapLittleInt16, "You must call FEndian::Init prior to calling this method.");
		return FEndian::SwapLittleInt16(LEData);
	}

	template <>
	inline Int32 FEndian::SwapLE(const Int32 LEData)
	{
		F_Assert(FEndian::SwapLittleInt32, "You must call FEndian::Init prior to calling this method.");
		return FEndian::SwapLittleInt32(LEData);
	}

	template <>
	inline UInt16 FEndian::SwapLE(const UInt16 LEData)
	{
		F_Assert(FEndian::SwapLittleUInt16, "You must call FEndian::Init prior to calling this method.");
		return FEndian::SwapLittleUInt16(LEData);
	}

	template <>
	inline UInt32 FEndian::SwapLE(const UInt32 LEData)
	{
		F_Assert(FEndian::SwapLittleUInt32, "You must call FEndian::Init prior to calling this method.");
		return FEndian::SwapLittleUInt32(LEData);
	}

	template <>
	inline Float32 FEndian::SwapLE(const Float32 LEData)
	{
		F_Assert(FEndian::SwapLittleFloat32, "You must call FEndian::Init prior to calling this method.");
		return FEndian::SwapLittleFloat32(LEData);
	}

	template <>
	inline Int16 FEndian::SwapBE(const Int16 BEData)
	{
		F_Assert(FEndian::SwapBigInt16, "You must call FEndian::Init prior to calling this method.");
		return FEndian::SwapBigInt16(BEData);
	}

	template <>
	inline Int32 FEndian::SwapBE(const Int32 BEData)
	{
		F_Assert(FEndian::SwapBigInt32, "You must call FEndian::Init prior to calling this method.");
		return FEndian::SwapBigInt32(BEData);
	}

	template <>
	inline UInt16 FEndian::SwapBE(const UInt16 BEData)
	{
		F_Assert(FEndian::SwapBigUInt16, "You must call FEndian::Init prior to calling this method.");
		return FEndian::SwapBigUInt16(BEData);
	}

	template <>
	inline UInt32 FEndian::SwapBE(const UInt32 BEData)
	{
		F_Assert(FEndian::SwapBigUInt32, "You must call FEndian::Init prior to calling this method.");
		return FEndian::SwapBigUInt32(BEData);
	}

	template <>
	inline Float32 FEndian::SwapBE(const Float32 BEData)
	{
		F_Assert(FEndian::SwapBigFloat32, "You must call FEndian::Init prior to calling this method.");
		return FEndian::SwapBigFloat32(BEData);
	}

	template <class T>
	T FEndian::InternalSwap(const T Data)
	{
		static_assert(false, "This function must be specialized.");
	}

	template <>
	inline Int16 FEndian::InternalSwap(const Int16 Data)
	{
		const Int16 Result = InternalSwap16(Data);
		return Result;
	}

	template <>
	inline Int32 FEndian::InternalSwap(const Int32 Data)
	{
		const Int32 Result = InternalSwap32(Data);
		return Result;
	}

	template <>
	inline UInt16 FEndian::InternalSwap(const UInt16 Data)
	{
		const UInt16 Result = InternalSwap16(Data);
		return Result;
	}

	template <>
	inline UInt32 FEndian::InternalSwap(const UInt32 Data)
	{
		const UInt32 Result = InternalSwap32(Data);
		return Result;
	}

	template <>
	inline Float32 FEndian::InternalSwap(const Float32 Data)
	{
		static_assert(sizeof(UInt32) == sizeof(Float32), "UInt32 size does not equal Float32 size.");
		union
		{
			UInt32 UInt32Data;
			Float32 Float32Data;
		} FloatSwap;

		FloatSwap.Float32Data = Data;
		FloatSwap.UInt32Data = FEndian::InternalSwap(FloatSwap.UInt32Data);

		return FloatSwap.Float32Data;
	}

	template <class T>
	T FEndian::InternalSwap16(const T Data16)
	{
		static_assert(sizeof(T) == 2, "You must use a 16 bit integer type with this function.");
		
		const T Result =
			((Data16 >> 8) & 0x00FF) +
			((Data16 << 8) & 0xFF00);
		return Result;
	}

	template <class T>
	T FEndian::InternalSwap32(const T Data32)
	{
		static_assert(sizeof(T) == 4, "You must use a 32 bit integer type with this function.");

		const T Result =
			((Data32 >> 24) & 0x000000FF) +
			((Data32 >> 8) & 0x0000FF00) +
			((Data32 << 8) & 0x00FF0000) +
			((Data32 << 24) & 0xFF000000);
		return Result;
	}

	template <class T>
	T FEndian::InternalNoSwap(const T Data)
	{
		return Data;
	}
}

#endif
