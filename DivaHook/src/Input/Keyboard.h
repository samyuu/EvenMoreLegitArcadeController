#pragma once
#include "IInputDevice.h"
#include "KeyboardState.h"
#include "../Utilities/Stopwatch.h"

namespace DivaHook::Input
{
	class Keyboard : public IInputDevice
	{
		const float DOUBLE_TAP_THRESHOLD = 200.0f;

	public:
		static Keyboard* GetInstance();
		
		void PollInput() override;
		bool IsDown(BYTE keycode);
		bool IsUp(BYTE keycode);
		bool IsTapped(BYTE keycode);
		bool IsDoubleTapped(BYTE keycode);
		bool IsReleased(BYTE keycode);

		bool WasDown(BYTE keycode);
		bool WasUp(BYTE keycode);

	private:
		Keyboard();
		KeyboardState lastState;
		KeyboardState currentState;

		BYTE KeyDoubleTapStates[KEYBOARD_KEYS];
		Utilities::Stopwatch KeyDoubleTapWatches[KEYBOARD_KEYS];

		static Keyboard* instance;
	};
}

