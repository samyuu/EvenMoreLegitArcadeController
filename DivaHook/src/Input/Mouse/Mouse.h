#pragma once
#include "../Bindings/IInputDevice.h"
#include "../DirectInput/DirectInputMouse.h"
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
		
		long GetMouseWheel();
		long GetDeltaMouseWheel();
		
		bool HasMoved();
		bool ScrolledUp();
		bool ScrolledDown();
		
		void SetPosition(int x, int y);

	private:
		Mouse();
		~Mouse();
		MouseState lastState;
		MouseState currentState;
		DirectInputMouse* directInputMouse = nullptr;

		static Mouse* instance;
	};
}

