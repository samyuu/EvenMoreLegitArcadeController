#pragma once
#include "IInputDevice.h"
#include "KeyboardState.h"

namespace DivaHook::Input
{
	class Keyboard : public IInputDevice
	{
	public:
		static Keyboard* GetInstance();
		
		void PollInput() override;
		bool IsDown(BYTE keycode);
		bool IsUp(BYTE keycode);
		bool IsTapped(BYTE keycode);
		bool IsReleased(BYTE keycode);

		bool WasDown(BYTE keycode);
		bool WasUp(BYTE keycode);

	private:
		Keyboard();
		KeyboardState lastState;
		KeyboardState currentState;

		static Keyboard* instance;
	};
}

