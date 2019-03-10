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
		delete customPlayerData;
	}

	const char* PlayerDataManager::GetDisplayName()
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
		if (playerData == nullptr)
			return;

		// don't need to overwrite the default values
		auto setIfNotEqual = [](int *target, int value, int comparison) 
		{
			if (value != comparison)
				*target = value;
		};

		setIfNotEqual(&playerData->level, customPlayerData->Level, 1);
		setIfNotEqual(&playerData->level_plate_id, customPlayerData->LevelPlateId, 0);
		setIfNotEqual(&playerData->vocaloid_point, customPlayerData->VocaloidPoint, 0);
		setIfNotEqual(&playerData->skin_equip, customPlayerData->SkinEquip, 0);
		setIfNotEqual(&playerData->btn_se_equip, customPlayerData->BtnSeEquip, -1);

		for (int i = 0; i < sizeof(playerData->module_equip) / sizeof(int); i++)
			setIfNotEqual(&playerData->module_equip[i], customPlayerData->ModuleEquip[i], 0);

		if (customPlayerData->PlayerName != nullptr)
		{
			playerData->field_D8 = 0x10;
			playerData->player_name = (char*)customPlayerData->PlayerName->c_str();
		}

		if (customPlayerData->LevelName != nullptr)
		{
			playerData->field_F4 = 0x10;
			playerData->level_name = (char*)customPlayerData->LevelName->c_str();
		}

		if (false && Input::Keyboard::GetInstance()->IsTapped(VK_F12))
		{
			printf("PlayerDataManager::Update(): Loading config...\n");
			LoadConfig();
		}
	}

	void PlayerDataManager::LoadConfig()
	{
		FileSystem::ConfigFile config(MainModule::GetModuleDirectory(), PLAYER_DATA_FILE_NAME);

		if (!config.OpenRead())
			return;

		if (customPlayerData != nullptr)
			delete customPlayerData;

		customPlayerData = new CustomPlayerData();

		auto parseInt = [&](const std::string &key)
		{
			std::string *stringBuffer;

			int result = 0;

			if (config.TryGetValue(key, stringBuffer))
			{
				result = std::stoi(stringBuffer->c_str());
				delete stringBuffer;
			}

			return result;
		};

		config.TryGetValue("player_name", customPlayerData->PlayerName);
		config.TryGetValue("level_name", customPlayerData->LevelName);

		customPlayerData->Level = parseInt("level");
		customPlayerData->LevelPlateId = parseInt("level_plate_id");
		customPlayerData->VocaloidPoint = parseInt("vocaloid_point");
		customPlayerData->ModuleEquip[0] = parseInt("module_equip[0]");
		customPlayerData->ModuleEquip[1] = parseInt("module_equip[1]");
		customPlayerData->SkinEquip = parseInt("skin_equip");
		customPlayerData->BtnSeEquip = parseInt("btn_se_equip");
	}
}
