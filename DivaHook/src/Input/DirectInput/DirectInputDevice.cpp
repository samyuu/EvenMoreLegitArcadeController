#include "DirectInputDevice.h"

namespace DivaHook::Input
{
	HRESULT DirectInputDevice::DI_CreateDevice(const GUID &guid)
	{
		HRESULT result = IDirectInputInstance->CreateDevice(guid, &directInputdevice, NULL);
		return result;
	}

	HRESULT DirectInputDevice::DI_SetDataFormat(LPCDIDATAFORMAT dataFormat)
	{
		HRESULT result = directInputdevice->SetDataFormat(dataFormat);
		return result;
	}

	HRESULT DirectInputDevice::DI_Acquire()
	{
		HRESULT result = directInputdevice->Acquire();
		return result;
	}

	HRESULT DirectInputDevice::DI_Unacquire()
	{
		HRESULT result = directInputdevice->Unacquire();
		return result;
	}

	HRESULT DirectInputDevice::DI_Release()
	{
		HRESULT result = directInputdevice->Release();
		return result;
	}

	HRESULT DirectInputDevice::DI_Poll()
	{
		HRESULT result = directInputdevice->Poll();
		return result;
	}

	HRESULT DirectInputDevice::DI_GetDeviceState(DWORD size, LPVOID data)
	{
		HRESULT result = directInputdevice->GetDeviceState(size, data);
		return result;
	}
}