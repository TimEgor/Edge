#include "DirectInputKeyboard.h"

#include "EdgeCommon/UtilsMacros.h"

#include "EdgeFramework/WindowController/Window.h"

#include <cassert>

class DirectInputKeyboardKeyMapper final
{
private:
	uint8_t m_keys[Edge::KeyboardKeyCount];

public:
	DirectInputKeyboardKeyMapper();

	uint8_t getKeyIndex(Edge::KeyboardKeys key) const;
};

DirectInputKeyboardKeyMapper::DirectInputKeyboardKeyMapper()
{
#define KEY(EDGE_KEY, DI_KEY)	\
	m_keys[static_cast<uint8_t>(EDGE_KEY)] = DI_KEY;

	KEY(Edge::KeyboardKeys::BackSpace, DIK_BACK);
	KEY(Edge::KeyboardKeys::Del, DIK_DELETE);
	KEY(Edge::KeyboardKeys::Tab, DIK_TAB);
	KEY(Edge::KeyboardKeys::Return, DIK_RETURN);
	KEY(Edge::KeyboardKeys::Pause, DIK_PAUSE);
	KEY(Edge::KeyboardKeys::Esc, DIK_ESCAPE);
	KEY(Edge::KeyboardKeys::Space, DIK_SPACE);
	KEY(Edge::KeyboardKeys::KeyPad0, DIK_NUMPAD0);
	KEY(Edge::KeyboardKeys::KeyPad1, DIK_NUMPAD1);
	KEY(Edge::KeyboardKeys::KeyPad2, DIK_NUMPAD2);
	KEY(Edge::KeyboardKeys::KeyPad3, DIK_NUMPAD3);
	KEY(Edge::KeyboardKeys::KeyPad4, DIK_NUMPAD4);
	KEY(Edge::KeyboardKeys::KeyPad5, DIK_NUMPAD5);
	KEY(Edge::KeyboardKeys::KeyPad6, DIK_NUMPAD6);
	KEY(Edge::KeyboardKeys::KeyPad7, DIK_NUMPAD7);
	KEY(Edge::KeyboardKeys::KeyPad8, DIK_NUMPAD8);
	KEY(Edge::KeyboardKeys::KeyPad9, DIK_NUMPAD9);
	KEY(Edge::KeyboardKeys::Dot, DIK_PERIOD);
	KEY(Edge::KeyboardKeys::Comma, DIK_COMMA);
	KEY(Edge::KeyboardKeys::Divide, DIK_DIVIDE);
	KEY(Edge::KeyboardKeys::Multiple, DIK_MULTIPLY);
	KEY(Edge::KeyboardKeys::Minus, DIK_SUBTRACT);
	KEY(Edge::KeyboardKeys::Plus, DIK_ADD);
	KEY(Edge::KeyboardKeys::Enter, DIK_RETURN);
	KEY(Edge::KeyboardKeys::ArrowUp, DIK_UP);
	KEY(Edge::KeyboardKeys::ArrowDown, DIK_DOWN);
	KEY(Edge::KeyboardKeys::ArrowRight, DIK_RIGHT);
	KEY(Edge::KeyboardKeys::ArrowLeft, DIK_LEFT);
	KEY(Edge::KeyboardKeys::Insert, DIK_INSERT);
	KEY(Edge::KeyboardKeys::Home, DIK_HOME);
	KEY(Edge::KeyboardKeys::End, DIK_END);
	KEY(Edge::KeyboardKeys::PageUp, DIK_PRIOR);
	KEY(Edge::KeyboardKeys::PageDown, DIK_NEXT);
	KEY(Edge::KeyboardKeys::F1, DIK_F1);
	KEY(Edge::KeyboardKeys::F2, DIK_F2);
	KEY(Edge::KeyboardKeys::F3, DIK_F3);
	KEY(Edge::KeyboardKeys::F4, DIK_F4);
	KEY(Edge::KeyboardKeys::F5, DIK_F5);
	KEY(Edge::KeyboardKeys::F6, DIK_F6);
	KEY(Edge::KeyboardKeys::F7, DIK_F7);
	KEY(Edge::KeyboardKeys::F8, DIK_F8);
	KEY(Edge::KeyboardKeys::F9, DIK_F9);
	KEY(Edge::KeyboardKeys::F10, DIK_F10);
	KEY(Edge::KeyboardKeys::F11, DIK_F11);
	KEY(Edge::KeyboardKeys::F12, DIK_F12);
	KEY(Edge::KeyboardKeys::F13, DIK_F13);
	KEY(Edge::KeyboardKeys::F14, DIK_F14);
	KEY(Edge::KeyboardKeys::F15, DIK_F15);
	KEY(Edge::KeyboardKeys::Alpha0, DIK_0);
	KEY(Edge::KeyboardKeys::Alpha1, DIK_1);
	KEY(Edge::KeyboardKeys::Alpha2, DIK_2);
	KEY(Edge::KeyboardKeys::Alpha3, DIK_3);
	KEY(Edge::KeyboardKeys::Alpha4, DIK_4);
	KEY(Edge::KeyboardKeys::Alpha5, DIK_5);
	KEY(Edge::KeyboardKeys::Alpha6, DIK_6);
	KEY(Edge::KeyboardKeys::Alpha7, DIK_7);
	KEY(Edge::KeyboardKeys::Alpha8, DIK_8);
	KEY(Edge::KeyboardKeys::Alpha9, DIK_9);
	KEY(Edge::KeyboardKeys::A, DIK_A);
	KEY(Edge::KeyboardKeys::B, DIK_B);
	KEY(Edge::KeyboardKeys::C, DIK_C);
	KEY(Edge::KeyboardKeys::D, DIK_D);
	KEY(Edge::KeyboardKeys::E, DIK_E);
	KEY(Edge::KeyboardKeys::F, DIK_F);
	KEY(Edge::KeyboardKeys::G, DIK_G);
	KEY(Edge::KeyboardKeys::H, DIK_H);
	KEY(Edge::KeyboardKeys::I, DIK_I);
	KEY(Edge::KeyboardKeys::J, DIK_J);
	KEY(Edge::KeyboardKeys::K, DIK_K);
	KEY(Edge::KeyboardKeys::L, DIK_L);
	KEY(Edge::KeyboardKeys::M, DIK_M);
	KEY(Edge::KeyboardKeys::N, DIK_N);
	KEY(Edge::KeyboardKeys::O, DIK_O);
	KEY(Edge::KeyboardKeys::P, DIK_P);
	KEY(Edge::KeyboardKeys::Q, DIK_Q);
	KEY(Edge::KeyboardKeys::R, DIK_R);
	KEY(Edge::KeyboardKeys::S, DIK_S);
	KEY(Edge::KeyboardKeys::T, DIK_T);
	KEY(Edge::KeyboardKeys::U, DIK_U);
	KEY(Edge::KeyboardKeys::V, DIK_V);
	KEY(Edge::KeyboardKeys::W, DIK_W);
	KEY(Edge::KeyboardKeys::X, DIK_X);
	KEY(Edge::KeyboardKeys::Y, DIK_Y);
	KEY(Edge::KeyboardKeys::Z, DIK_Z);
	KEY(Edge::KeyboardKeys::Colons, DIK_COLON);
	KEY(Edge::KeyboardKeys::BracketsRight, DIK_RBRACKET);
	KEY(Edge::KeyboardKeys::BracketsLeft, DIK_LBRACKET);
	KEY(Edge::KeyboardKeys::BackSlash, DIK_BACKSLASH);
	KEY(Edge::KeyboardKeys::Quotes, DIK_APOSTROPHE);
	KEY(Edge::KeyboardKeys::Tilde, DIK_GRAVE);
	KEY(Edge::KeyboardKeys::NumLock, DIK_NUMLOCK);
	KEY(Edge::KeyboardKeys::CapsLock, DIK_CAPITAL);
	KEY(Edge::KeyboardKeys::ScrollLock, DIK_SCROLL);
	KEY(Edge::KeyboardKeys::ShiftRight, DIK_RSHIFT);
	KEY(Edge::KeyboardKeys::ShiftLeft, DIK_LSHIFT);
	KEY(Edge::KeyboardKeys::ControlRight, DIK_RCONTROL);
	KEY(Edge::KeyboardKeys::ControlLeft, DIK_LCONTROL);
	KEY(Edge::KeyboardKeys::AltRight, DIK_RALT);
	KEY(Edge::KeyboardKeys::AltLeft, DIK_LALT);
	KEY(Edge::KeyboardKeys::SystemRight, DIK_RWIN);
	KEY(Edge::KeyboardKeys::SystemLeft, DIK_LWIN);
}

uint8_t DirectInputKeyboardKeyMapper::getKeyIndex(Edge::KeyboardKeys key) const
{
	return m_keys[static_cast<uint8_t>(key)];
}

bool EdgeWin32::DirectInputKeyboard::init()
{
	EDGE_CHECK_INITIALIZATION(initDevice());

	getDirectInputDevice()->SetDataFormat(&c_dfDIKeyboard);

	return true;
}

void EdgeWin32::DirectInputKeyboard::release()
{
	releaseDevice();
}

void EdgeWin32::DirectInputKeyboard::update()
{
	static DirectInputKeyboardKeyMapper keyMapper;

	m_keyData.reset();

	const HRESULT result = getDirectInputDevice()->GetDeviceState(sizeof(m_deviceKeys), m_deviceKeys);
	if (result != DI_OK)
	{
		return;
	}

	for (Edge::KeyboardKey keyIndex = 0; keyIndex < static_cast<Edge::KeyboardKey>(Edge::KeyboardKeys::MAX_KEY); ++keyIndex)
	{
		const uint8_t deviceKeyIndex = keyMapper.getKeyIndex(static_cast<Edge::KeyboardKeys>(keyIndex));
		m_keyData.m_values[keyIndex] = (m_deviceKeys[deviceKeyIndex] & 0x80) ? 1.0f : 0.0f;
	}
}

void EdgeWin32::DirectInputKeyboard::onWindowSet(const Edge::Window& window, bool exclusiveUsing)
{
	setDeviceCooperativeLevel(window, exclusiveUsing);
}

void EdgeWin32::DirectInputKeyboard::acquire()
{
	acquireDevice();
}

void EdgeWin32::DirectInputKeyboard::unacquire()
{
	unacquireDevice();
}
