#include "TouchPanelEmulator.h"
#include "../../Constants.h"
#include "../../Input/Mouse/Mouse.h"

#define TOUCH_PANEL_CONNECTED 1

using namespace DivaHook::Input;

namespace DivaHook::Components
{
	TouchPanelEmulator::TouchPanelEmulator()
	{
	}

	TouchPanelEmulator::~TouchPanelEmulator()
	{
	}

	const char* TouchPanelEmulator::GetDisplayName()
	{
		return "touch_panel_emulator";
	}

	void TouchPanelEmulator::Initialize()
	{
		touchPanelState = GetTouchStatePtr((void*)TASK_TOUCH_ADDRESS);
	}

	void TouchPanelEmulator::Update()
	{
		touchPanelState->ConnectionState = TOUCH_PANEL_CONNECTED;
	}

	void TouchPanelEmulator::UpdateInput()
	{
		auto keyboard = Keyboard::GetInstance();
		auto pos = Mouse::GetInstance()->GetRelativePosition();

		touchPanelState->XPosition = (float)pos.x;
		touchPanelState->YPosition = (float)pos.y;

		touchPanelState->ContactType = GetContactType(keyboard);
		touchPanelState->Pressure = (float)(touchPanelState->ContactType != CONTACT_UP);
	}

	TouchPanelState* TouchPanelEmulator::GetTouchStatePtr(void *address)
	{
		return (TouchPanelState*)address;
	}

	ContactType TouchPanelEmulator::GetContactType(Keyboard *keyboard)
	{
		bool down = keyboard->IsDown(VK_LBUTTON);
		bool released = keyboard->IsReleased(VK_LBUTTON);

		return (down ? CONTACT_DOWN : released ? CONTACT_RELEASED : CONTACT_UP);
	}
}
