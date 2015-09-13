#ifndef PHOENIX_INPUT_CODES_H
#define PHOENIX_INPUT_CODES_H

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	enum class EKeyCode : Int32
	{
		//Alphabet
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		//Numeric
		Alpha0 = 48,
		Alpha1 = 49,
		Alpha2 = 50,
		Alpha3 = 51,
		Alpha4 = 52,
		Alpha5 = 53,
		Alpha6 = 54,
		Alpha7 = 55,
		Alpha8 = 56,
		Alpha9 = 57,

		//Symbols
		Space			= 32,
		Apostrophe		= 39,  /* ' */
		Comma			= 44,  /* , */
		Minus			= 45,  /* - */
		Period			= 46,  /* . */
		Slash			= 47,  /* / */
		SemiColon		= 59,  /* ; */
		Equal			= 61,  /* = */
		LeftBracket		= 91,  /* [ */
		Backslash		= 92,  /* \ */
		RightBracket	= 93,  /* ] */
		Tilde			= 96,  /* ` */

		//Function Keys
		Esc				= 256,
		Enter			= 257,
		Tab				= 258,
		Backspace		= 259,
		Insert			= 260,
		Delete			= 261,
		Right			= 262,
		Left			= 263,
		Down			= 264,
		Up				= 265,
		PageUp			= 266,
		PageDown		= 267,
		Home			= 268,
		End				= 269,
		CapsLock		= 280,
		ScrollLock		= 281,
		NumLock			= 282,
		PrintScreen		= 283,
		Pause			= 284,
		F1				= 290,
		F2				= 291,
		F3				= 292,
		F4				= 293,
		F5				= 294,
		F6				= 295,
		F7				= 296,
		F8				= 297,
		F9				= 298,
		F10				= 299,
		F11				= 300,
		F12				= 301,
		F13				= 302,
		F14				= 303,
		F15				= 304,
		F16				= 305,
		F17				= 306,
		F18				= 307,
		F19				= 308,
		F20				= 309,
		F21				= 310,
		F22				= 311,
		F23				= 312,
		F24				= 313,
		F25				= 314,
		NumPad0			= 320,
		NumPad1			= 321,
		NumPad2			= 322,
		NumPad3			= 323,
		NumPad4			= 324,
		NumPad5			= 325,
		NumPad6			= 326,
		NumPad7			= 327,
		NumPad8			= 328,
		NumPad9			= 329,
		NumPadPeriod	= 330,
		NumPadDive		= 331,
		NumPadMultiply	= 332,
		NumPadSubtract	= 333,
		NumPadAdd		= 334,
		NumPadEnter		= 335,
		NumPadEqual		= 336,
		LeftShift		= 340,
		LeftControl		= 341,
		LeftAlt			= 342,
		RightShift		= 344,
		RightControl	= 345,
		RightAlt		= 346,

		Unknown = -1,
	};
}

#endif
