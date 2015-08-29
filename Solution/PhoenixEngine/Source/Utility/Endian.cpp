#include "Utility/Endian.h"

using namespace Phoenix;

FEndian::TSwapFunc<SI16> FEndian::SwapLittleSI16;
FEndian::TSwapFunc<SI32> FEndian::SwapLittleSI32;
FEndian::TSwapFunc<UI16> FEndian::SwapLittleUI16;
FEndian::TSwapFunc<UI32> FEndian::SwapLittleUI32;
FEndian::TSwapFunc<F32> FEndian::SwapLittleF32;

FEndian::TSwapFunc<SI16> FEndian::SwapBigSI16;
FEndian::TSwapFunc<SI32> FEndian::SwapBigSI32;
FEndian::TSwapFunc<UI16> FEndian::SwapBigUI16;
FEndian::TSwapFunc<UI32> FEndian::SwapBigUI32;
FEndian::TSwapFunc<F32> FEndian::SwapBigF32;
