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
		POINT GetRelativePosition();
		POINT GetDeltaPosition();
		bool HasMoved();
		void SetPosition(int x, int y);

	private:
		Mouse();
		MouseState lastState;
		MouseState currentState;

		static Mouse* instance;
	};
}

