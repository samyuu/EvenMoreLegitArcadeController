#pragma once
#include "EmulatorComponent.h"
#include "PlayerData.h"
#include <string>

namespace DivaHook::Components
{
	struct CustomPlayerData
	{
		std::string *PlayerName;
		std::string *LevelName;
		int LevelNo;
		int LevelPlateId;
		int SkinEquip;
		int BtnSeEquip;
		int VocaloidPoint;
		int ModuleEquip[2];
	};

	class PlayerDataManager : public EmulatorComponent
	{
	public:
		PlayerDataManager();
		~PlayerDataManager();

		virtual const char* GetDisplayName() override;

		virtual void Initialize() override;
		virtual void Update() override;

	private:
		PlayerData* playerData;
		CustomPlayerData customPlayerData;

		void LoadConfig();
	};
}

