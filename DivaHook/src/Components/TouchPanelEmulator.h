#pragma once
#include "EmulatorComponent.h"
#include "TouchState.h"

namespace DivaHook::Components
{
	class TouchPanelEmulator : public EmulatorComponent
	{
		const int TASK_TOUCH_ADDRESS = 0x0108CD60;

	public:
		TouchPanelEmulator();
		~TouchPanelEmulator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void UpdateInput() override;

		TouchState* State;
		TouchState* GetTouchStatePtr(int address);
	};
}

