#include "TouchPanelEmulator.h"
#include <iostream>
#include "../Input/Mouse.h"
#include "../Input/Keyboard.h"
#include "../MainModule.h"

using namespace DivaHook::Input;

namespace DivaHook::Components
{
	TouchPanelEmulator::TouchPanelEmulator()
	{
	}

	TouchPanelEmulator::~TouchPanelEmulator()
	{
	}

	void TouchPanelEmulator::Initialize()
	{
		State = GetTouchStatePtr(TASK_TOUCH_ADDRESS);
	}

	void TouchPanelEmulator::Update()
	{
		State->ConnectionState = 1;
	}

	void TouchPanelEmulator::UpdateInput()
	{
		// TODO: rescale TouchReaction aet position
		auto keyboard = Keyboard::GetInstance();
		auto pos = Mouse::GetInstance()->GetPosition();

		ScreenToClient(MainModule::DivaWindowHandle, &pos);

		State->XPosition = (float)pos.x;
		State->YPosition = (float)pos.y;

		bool tapped = keyboard->IsTapped(VK_LBUTTON);
		bool released = keyboard->IsReleased(VK_LBUTTON);

		State->ContactType = (tapped ? 0x2 : released ? 0x1 : 0x0);
		State->Pressure = (float)(State->ContactType != 0);
	}

	TouchState* TouchPanelEmulator::GetTouchStatePtr(int address)
	{
		return (TouchState*)(int*)address;
	}
}
