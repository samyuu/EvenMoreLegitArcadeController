#include "CustomPlayerData.h"

namespace DivaHook::Components
{
	CustomPlayerData::CustomPlayerData()
	{
	}

	CustomPlayerData::~CustomPlayerData()
	{
		if (PlayerName != nullptr)
			delete PlayerName;

		if (LevelName != nullptr)
			delete LevelName;
	}
}