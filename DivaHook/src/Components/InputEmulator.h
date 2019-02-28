#pragma once
#include <functional>
#include <Windows.h>
#include "EmulatorComponent.h"
#include "InputState.h"
#include "../Input/Binding.h"

namespace DivaHook::Components
{
	class InputEmulator : public EmulatorComponent
	{
	public:
		InputEmulator();
		~InputEmulator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void UpdateInput() override;

		virtual void OnFocusLost() override;

	private:
		InputState* inputState;

		InputState* GetInputStatePtr(int address);
		JvsButtons GetJvsButtonsState(bool(*buttonTestFunc)(void*));

		void UpdateInputBit(uint32_t bit, uint8_t keycode);
	};
}

