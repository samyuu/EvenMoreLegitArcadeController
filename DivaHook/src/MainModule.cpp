#include "MainModule.h"

namespace DivaHook
{
	const wchar_t* MainModule::DivaWindowName = L"Hatsune Miku Project DIVA Arcade";

	HWND MainModule::DivaWindowHandle;
	HMODULE MainModule::Module;
}