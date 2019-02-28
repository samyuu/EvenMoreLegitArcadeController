#include "TouchPanelEmulator.h"
#include <iostream>
#include "../Constants.h"
#include "../Input/Mouse.h"
#include "../Input/Keyboard.h"

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
		state = GetTouchStatePtr(TASK_TOUCH_ADDRESS);
	}

	void TouchPanelEmulator::Update()
	{
		state->ConnectionState = 1;
	}

	void TouchPanelEmulator::UpdateInput()
	{
		// TODO: rescale TouchReaction aet position
		auto keyboard = Keyboard::GetInstance();
		auto pos = Mouse::GetInstance()->GetRelativePosition();

		state->XPosition = (float)pos.x;
		state->YPosition = (float)pos.y;

		bool tapped = keyboard->IsTapped(VK_LBUTTON);
		bool released = keyboard->IsReleased(VK_LBUTTON);

		state->ContactType = (tapped ? 0x2 : released ? 0x1 : 0x0);
		state->Pressure = (float)(state->ContactType != 0);
	}

	TouchState* TouchPanelEmulator::GetTouchStatePtr(int address)
	{
		return (TouchState*)address;
	}
}
