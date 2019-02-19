#include "Mouse.h"

namespace DivaHook::Input
{
	Mouse* Mouse::instance;

	Mouse::Mouse()
	{
	}

	Mouse* Mouse::GetInstance()
	{
		if (instance == nullptr)
			instance = new Mouse();

		return instance;
	}

	POINT Mouse::GetPosition()
	{
		return currentState.point;
	}

	void Mouse::PollInput()
	{
		lastState = currentState;
		GetCursorPos(&currentState.point);
	}
}
