#include "DirectInputMouse.h"

namespace DivaHook::Input
{
	DirectInputMouse::DirectInputMouse()
	{
		HRESULT result = NULL;

		result = DI_CreateDevice(GUID_SysMouse);
		result = DI_SetDataFormat(&c_dfDIMouse);
		result = DI_Acquire();
	}

	DirectInputMouse::~DirectInputMouse()
	{
		if (directInputdevice == nullptr)
			return;

		HRESULT result = NULL;

		result = DI_Unacquire();
		result = DI_Release();
	}

	bool DirectInputMouse::Poll()
	{
		HRESULT result = NULL;

		result = DI_Poll();
		result = DI_GetDeviceState(sizeof(mouseState), &mouseState);

		return !FAILED(result);
	}
}