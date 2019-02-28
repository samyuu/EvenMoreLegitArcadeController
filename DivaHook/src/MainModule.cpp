#include "MainModule.h"

namespace DivaHook
{
	const wchar_t* MainModule::DivaWindowName = L"Hatsune Miku Project DIVA Arcade";
	const wchar_t* MainModule::GlutDefaultName = L"GLUT";

	HWND MainModule::DivaWindowHandle;
	HMODULE MainModule::Module;
}