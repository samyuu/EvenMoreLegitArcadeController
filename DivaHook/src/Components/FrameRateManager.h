#pragma once
#include "EmulatorComponent.h"

namespace DivaHook::Components
{
	class FrameRateManager : public EmulatorComponent
	{
	public:
		FrameRateManager();
		~FrameRateManager();

		virtual const char* GetDisplayName() override;

		virtual void Initialize() override;
		virtual void Update() override;

	private:
		float *frameSpeed;
		float *aetFrameDuration;
		float defaultAetFrameDuration;
	};
}

