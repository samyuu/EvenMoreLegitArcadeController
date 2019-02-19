#pragma once
#include "IInputDevice.h"
#include "MouseState.h"

namespace DivaHook::Input
{
	class Mouse : public IInputDevice
	{
	public:
		static Mouse* GetInstance();

		void PollInput() override;
		POINT GetPosition();

	private:
		Mouse();
		MouseState lastState;
		MouseState currentState;

		static Mouse* instance;
	};
}

