#include "Utility/Endian.h"

using namespace Phoenix;

FEndian::TSwapFunc<Int16> FEndian::SwapLittleInt16;
FEndian::TSwapFunc<Int32> FEndian::SwapLittleInt32;
FEndian::TSwapFunc<UInt16> FEndian::SwapLittleUInt16;
FEndian::TSwapFunc<UInt32> FEndian::SwapLittleUInt32;
FEndian::TSwapFunc<Float32> FEndian::SwapLittleFloat32;

FEndian::TSwapFunc<Int16> FEndian::SwapBigInt16;
FEndian::TSwapFunc<Int32> FEndian::SwapBigInt32;
FEndian::TSwapFunc<UInt16> FEndian::SwapBigUInt16;
FEndian::TSwapFunc<UInt32> FEndian::SwapBigUInt32;
FEndian::TSwapFunc<Float32> FEndian::SwapBigFloat32;
