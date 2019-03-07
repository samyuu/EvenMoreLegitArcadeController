#include "PlayerDataManager.h"
#include <string>
#include "../MainModule.h"
#include "../Constants.h"
#include "../Input/Keyboard.h"
#include "../FileSystem/ConfigFile.h"

const std::string PLAYER_DATA_FILE_NAME = "playerdata.ini";

namespace DivaHook::Components
{
	PlayerDataManager::PlayerDataManager()
	{
	}

	PlayerDataManager::~PlayerDataManager()
	{
	}

	const char *PlayerDataManager::GetDisplayName()
	{
		return "player_data_manager";
	}

	void PlayerDataManager::Initialize()
	{
		playerData = (PlayerData*)PLAYER_DATA_ADDRESS;

		LoadConfig();
	}

	void PlayerDataManager::Update()
	{
		playerData->level = customPlayerData.LevelNo;
		playerData->level_plate_id = customPlayerData.LevelPlateId;
		playerData->skin_equip = customPlayerData.SkinEquip;
		playerData->btn_se_equip = customPlayerData.BtnSeEquip;
		playerData->vocaloid_point = customPlayerData.VocaloidPoint;

		for (int i = 0; i < sizeof(playerData->module_equip) / sizeof(int); i++)
			playerData->module_equip[i] = customPlayerData.ModuleEquip[i];

		if (customPlayerData.PlayerName != nullptr)
			playerData->player_name = (char*)customPlayerData.PlayerName->c_str();
		if (customPlayerData.LevelName != nullptr)
			playerData->level_name = (char*)customPlayerData.LevelName->c_str();

		//if (Input::Keyboard::GetInstance()->IsTapped(VK_F12))
		//{
		//	printf("PlayerDataManager::Update(): Loading config...\n");
		//	LoadConfig();
		//}
	}

	void PlayerDataManager::LoadConfig()
	{
		FileSystem::ConfigFile config(MainModule::GetModuleDirectory(), PLAYER_DATA_FILE_NAME);

		if (!config.OpenRead())
			return;

		std::string *customName;
		std::string *levelName;

		if (config.TryGetValue("player_name", customName))
			customPlayerData.PlayerName = customName;
		if (config.TryGetValue("level_name", levelName))
			customPlayerData.LevelName = levelName;

		auto parseInt = [&](const std::string &key)
		{
			std::string *stringBuffer;

			int result;

			if (config.TryGetValue(key, stringBuffer))
			{
				result = std::stoi(stringBuffer->c_str());
				delete stringBuffer;
			}

			return result;
		};

		customPlayerData.LevelNo = parseInt("level");
		customPlayerData.LevelPlateId = parseInt("level_plate_id");
		customPlayerData.SkinEquip = parseInt("skin_equip");
		customPlayerData.BtnSeEquip = parseInt("btn_se_equip");
		customPlayerData.VocaloidPoint = parseInt("vocaloid_point");
		customPlayerData.ModuleEquip[0] = parseInt("module_equip[0]");
		customPlayerData.ModuleEquip[1] = parseInt("module_equip[1]");
	}
}
