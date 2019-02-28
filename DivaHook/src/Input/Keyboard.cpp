#include "Keyboard.h"

namespace DivaHook::Input
{
	Keyboard* Keyboard::instance;

	Keyboard::Keyboard()
	{
	}

	Keyboard* Keyboard::GetInstance()
	{
		if (instance == nullptr)
			instance = new Keyboard();

		return instance;
	}

	void Keyboard::PollInput()
	{
		lastState = currentState;

		for (BYTE i = 0; i < KEYBOARD_KEYS; i++)
		{
			currentState.KeyStates[i] = GetAsyncKeyState(i) < 0;

			KeyDoubleTapStates[i] = IsTapped(i) ? KeyDoubleTapWatches[i].Restart() <= DOUBLE_TAP_THRESHOLD : false;
		}
	}

	bool Keyboard::IsDown(BYTE keycode)
	{
		return currentState.IsDown(keycode);
	}

	bool Keyboard::IsUp(BYTE keycode)
	{
		return !IsDown(keycode);
	}

	bool Keyboard::IsTapped(BYTE keycode)
	{
		return IsDown(keycode) && WasUp(keycode);
	}

	bool Keyboard::IsDoubleTapped(BYTE keycode)
	{
		return KeyDoubleTapStates[keycode];
	}

	bool Keyboard::IsReleased(BYTE keycode)
	{
		return IsUp(keycode) && WasDown(keycode);
	}

	inline bool Keyboard::WasDown(BYTE keycode)
	{
		return lastState.IsDown(keycode);
	}

	inline bool Keyboard::WasUp(BYTE keycode)
	{
		return !WasDown(keycode);
	}
}
