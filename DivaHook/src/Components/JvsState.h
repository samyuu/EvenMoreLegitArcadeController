#pragma once
#include "JvsButtons.h"

namespace DivaHook::Components
{
	struct JvsState
	{
		JvsButtons TappedState;
		int Padding[7];
		JvsButtons DownState;
	};
}
