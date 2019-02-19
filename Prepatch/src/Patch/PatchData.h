#pragma once
#include <Windows.h>

namespace Patch
{
	struct PatchData
	{
		DWORD Address;
		DWORD Length;
		BYTE* OriginalBytes;
		BYTE* PatchedBytes;

		PatchData();
		~PatchData();
	};
}
