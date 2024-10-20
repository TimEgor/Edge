#pragma once

#include "InputDeviceKeyData.h"

namespace Edge
{
	using KeyboardKey = InputDeviceKeyData::KeyIndex;

	enum class KeyboardKeys : KeyboardKey
	{
		BackSpace,
		Del,
		Tab,
		Return,
		Pause,
		Esc,
		Space,
		KeyPad0,
		KeyPad1,
		KeyPad2,
		KeyPad3,
		KeyPad4,
		KeyPad5,
		KeyPad6,
		KeyPad7,
		KeyPad8,
		KeyPad9,
		Dot,
		Comma,
		Divide,
		Multiple,
		Minus,
		Plus,
		Enter,
		ArrowUp,
		ArrowDown,
		ArrowRight,
		ArrowLeft,
		Insert,
		Home,
		End,
		PageUp,
		PageDown,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		Alpha0,
		Alpha1,
		Alpha2,
		Alpha3,
		Alpha4,
		Alpha5,
		Alpha6,
		Alpha7,
		Alpha8,
		Alpha9,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		Colons,
		BracketsRight,
		BracketsLeft,
		BackSlash,
		Quotes,
		Tilde,
		NumLock,
		CapsLock,
		ScrollLock,
		ShiftRight,
		ShiftLeft,
		ControlRight,
		ControlLeft,
		AltRight,
		AltLeft,
		SystemRight,
		SystemLeft,

		MAX_KEY = SystemLeft
	};

	constexpr KeyboardKey KeyboardKeyCount = static_cast<KeyboardKey>(KeyboardKeys::MAX_KEY);

	inline KeyboardKey GetKeyboardKey(KeyboardKeys key) { return static_cast<KeyboardKey>(key); }
}
