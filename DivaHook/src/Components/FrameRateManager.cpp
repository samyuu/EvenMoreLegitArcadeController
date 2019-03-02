#include "FrameRateManager.h"
#include "../Constants.h"
#include <stdio.h>
#include <windows.h>

namespace DivaHook::Components
{
	FrameRateManager::FrameRateManager()
	{
	}

	FrameRateManager::~FrameRateManager()
	{
	}

	const char* FrameRateManager::GetDisplayName()
	{
		return "frame_rate_manager";
	}

	void FrameRateManager::Initialize()
	{
		frameSpeed = (float*)FRAME_SPEED_ADDRESS;
		aetFrameDuration = (float*)AET_FRAME_DURATION_ADDRESS;

		// The default is expected to be 1.0 / 60.0
		defaultAetFrameDuration = *aetFrameDuration;

		// This const variable is stored inside a data segment so we don't want to throw any access violations
		DWORD oldProtect;
		VirtualProtect((void*)AET_FRAME_DURATION_ADDRESS, sizeof(float), PAGE_EXECUTE_READWRITE, &oldProtect);
	}

	void FrameRateManager::Update()
	{
		float frameRate = GetFrameRate();

		float commonRefreshRates[]
		{
			60.0f,
			120.0f,
			144.0f,
			240.0f,
		};

		const float threshold = 4.0f;

		for (int i = 0; i < sizeof(commonRefreshRates) / sizeof(float); i++)
		{
			float refreshRate = commonRefreshRates[i];

			if (frameRate > refreshRate - threshold && frameRate < refreshRate + threshold)
				frameRate = refreshRate;
		}

		*aetFrameDuration = 1.0f / frameRate;
		*frameSpeed = *aetFrameDuration / defaultAetFrameDuration;
	}
}
