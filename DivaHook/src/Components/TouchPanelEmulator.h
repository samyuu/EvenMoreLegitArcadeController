#pragma once
#include "EmulatorComponent.h"
#include "TouchState.h"

namespace DivaHook::Components
{
	class TouchPanelEmulator : public EmulatorComponent
	{
	public:
		TouchPanelEmulator();
		~TouchPanelEmulator();

		virtual const char* GetDisplayName() override;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void UpdateInput() override;

	private:
		TouchState* state;
		TouchState* GetTouchStatePtr(int address);
	};
}

