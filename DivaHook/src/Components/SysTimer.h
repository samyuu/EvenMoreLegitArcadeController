#pragma once
#include "EmulatorComponent.h"

namespace DivaHook::Components
{
	class SysTimer : public EmulatorComponent
	{
		const int SEL_PV_TIME_ADDRESS = 0x01046BC4;
		const int SYS_TIME_FACTOR = 60;
		
		const int SEL_PV_FREEZE_TIME = 39;

	public:
		SysTimer();
		~SysTimer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void UpdateInput() override;

	private:
		int* selPvTime;
		int* GetSysTimePtr(int address);
	};
}

