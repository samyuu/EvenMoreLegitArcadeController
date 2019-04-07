#pragma once
#include "DirectInput.h"

namespace DivaHook::Input
{
	class DirectInputDevice
	{
	public:
		virtual bool Poll() = 0;

	protected:
		IDirectInputDevice8 *directInputdevice;

		HRESULT DI_CreateDevice(const GUID& guid);
		HRESULT DI_SetDataFormat(LPCDIDATAFORMAT dataFormat);
		HRESULT DI_Acquire();
		HRESULT DI_Unacquire();
		HRESULT DI_Release();
		HRESULT DI_Poll();
		HRESULT DI_GetDeviceState(DWORD size, LPVOID data);
	};
}