#pragma once
#include "../EmulatorComponent.h"
#include "TouchPanelState.h"
#include "../../Input/Keyboard/Keyboard.h"

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
		TouchPanelState* touchPanelState;
		TouchPanelState* GetTouchStatePtr(void *address);

		ContactType GetContactType(Input::Keyboard *keyboard);
	};
}

