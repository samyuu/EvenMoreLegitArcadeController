#pragma once
#include "IInputBinding.h"
#include <windows.h>
#include <vector>

namespace DivaHook::Input
{
	class KeyboardBinding : public IInputBinding
	{
	public:
		BYTE Keycode;

		KeyboardBinding(BYTE keycode);
		~KeyboardBinding();

		bool IsDown() override;
		bool IsTapped() override;
		bool IsReleased() override;
		bool IsDoubleTapped() override;
	};
}
