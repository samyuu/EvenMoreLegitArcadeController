#include "MainModule.h"
#include <filesystem>

namespace DivaHook
{
	typedef std::filesystem::path fspath;

	const wchar_t* MainModule::DivaWindowName = L"Hatsune Miku Project DIVA Arcade";
	const wchar_t* MainModule::GlutDefaultName = L"GLUT";

	HWND MainModule::DivaWindowHandle;
	HMODULE MainModule::Module;

	std::string MainModule::GetModuleDirectory()
	{
		CHAR modulePathBuffer[MAX_PATH];
		GetModuleFileNameA(MainModule::Module, modulePathBuffer, MAX_PATH);

		fspath configPath = fspath(modulePathBuffer).parent_path();

		return std::string(configPath.u8string());
	}
}