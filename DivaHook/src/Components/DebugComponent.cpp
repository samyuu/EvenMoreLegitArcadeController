#include "DebugComponent.h"
#include <iostream>
#include <Windows.h>
#include "InputState.h"
#include "GameState.h"
#include "PlayerData.h"
#include "../Input/Keyboard.h"
#include "../Constants.h"

namespace DivaHook::Components
{
	DebugComponent::DebugComponent()
	{
	}

	DebugComponent::~DebugComponent()
	{
	}

	const char* DebugComponent::GetDisplayName()
	{
		return "debug_component";
	}

	void DebugComponent::Initialize()
	{
		printf("DebugComponent::Initialize(): Initialized\n");
	}

	void DebugComponent::Update()
	{
		return;
	}

	void DebugComponent::UpdateInput()
	{
		auto keyboard = Input::Keyboard::GetInstance();

		typedef void ChangeGameState(GameState);
		ChangeGameState* changeBaseState = (ChangeGameState*)0x0045C100;

		typedef void ChangeLogGameState(GameState, SubGameState);
		ChangeLogGameState* changeSubState = (ChangeLogGameState*)0x0045C290;

		if (keyboard->IsTapped(VK_F4)) changeBaseState(GS_ADVERTISE);
		if (keyboard->IsTapped(VK_F5)) changeBaseState(GS_GAME);
		if (keyboard->IsTapped(VK_F6)) changeBaseState(GS_DATA_TEST);
		if (keyboard->IsTapped(VK_F7)) changeBaseState(GS_TEST_MODE);
		if (keyboard->IsTapped(VK_F8)) changeBaseState(GS_APP_ERROR);
	}
}
