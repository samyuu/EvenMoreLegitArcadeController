#pragma once
#include "EmulatorComponent.h"

namespace DivaHook::Components
{
	class DebugComponent : public EmulatorComponent
	{
	public:
		DebugComponent();
		~DebugComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void UpdateInput() override;
	};
}

