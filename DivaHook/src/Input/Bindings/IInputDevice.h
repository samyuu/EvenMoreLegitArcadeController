#pragma once

namespace DivaHook::Input
{
	class IInputDevice
	{
	public:
		virtual void PollInput() = 0;
	};
}
