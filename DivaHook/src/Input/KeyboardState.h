#pragma once
#include <windows.h>

namespace DivaHook::Input
{
	struct KeyboardState
	{
		BYTE KeyStates[0xFF];
	
		bool IsDown(BYTE keycode);
	};
}

