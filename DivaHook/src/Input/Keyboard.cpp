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

		for (BYTE i = 0; i < 0xFF; i++)
			currentState.KeyStates[i] = GetAsyncKeyState(i) < 0;
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
