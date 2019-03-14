#include "ScaleComponent.h"
#include <iostream>
#include <Windows.h>
#include "Input/InputState.h"
#include "GameState.h"
#include "PlayerData.h"
#include "../Input/Keyboard.h"
#include "../Constants.h"
#include "wtypes.h"
#include "../MainModule.h"

namespace DivaHook::Components
{
	ScaleComponent::ScaleComponent()
	{
	}

	ScaleComponent::~ScaleComponent()
	{
	}

	const char* ScaleComponent::GetDisplayName()
	{
		return "scale_component";
	}

	void ScaleComponent::Initialize()
	{
		printf("ScaleComponent::Initialize(): Initialized\n");
	}

	void ScaleComponent::Update()
	{
		uiAspectRatio = (float*)UI_ASPECT_RATIO_ADDRESS;
		uiWidth = (float*)UI_WIDTH_ADDRESS;
		uiHeight = (float*)UI_HEIGHT_ADDRESS;
		fb1Height = (int*)FB1_HEIGHT_ADDRESS;
		fb1Width = (int*)FB1_WIDTH_ADDRESS;
		fb2Height = (int*)FB2_HEIGHT_ADDRESS;
		fb2Width = (int*)FB2_WIDTH_ADDRESS;
		fbAspectRatio = (double*)FB_ASPECT_RATIO_ADDRESS;
		RECT hWindow;
		GetClientRect(DivaHook::MainModule::DivaWindowHandle, &hWindow);
		*uiAspectRatio = (float)(hWindow.right - hWindow.left) / (float)(hWindow.bottom - hWindow.top);
		*fbAspectRatio = (double)(hWindow.right - hWindow.left) / (double)(hWindow.bottom - hWindow.top);
		*uiWidth = hWindow.right - hWindow.left;
		*uiHeight = hWindow.bottom - hWindow.top;
		*fb1Width = hWindow.right - hWindow.left;
		*fb1Height = hWindow.bottom - hWindow.top;
		*fb2Width = hWindow.right - hWindow.left;
		*fb2Height = hWindow.bottom - hWindow.top;
		return;
	}

	void ScaleComponent::UpdateInput()
	{
		
	}
}
