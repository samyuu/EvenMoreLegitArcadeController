#include "SysTimer.h"
#include "../Constants.h"

namespace DivaHook::Components
{
	SysTimer::SysTimer()
	{
	}

	SysTimer::~SysTimer()
	{
	}

	void SysTimer::Initialize()
	{
		selPvTime = GetSysTimePtr(SEL_PV_TIME_ADDRESS);
	}

	void SysTimer::Update()
	{
		// account for the decrement that occures during this frame
		*selPvTime = SEL_PV_FREEZE_TIME * SYS_TIME_FACTOR + 1;
	}

	void SysTimer::UpdateInput()
	{
		return;
	}

	int* SysTimer::GetSysTimePtr(int address)
	{
		return (int*)address;
	}
}
