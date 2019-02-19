#include <iostream>
#include "windows.h"
#include "JvsEmulator.h"
#include <fstream>
#include <algorithm>
#include <filesystem>
#include "../MainModule.h"
#include "../EnumBitwiseOperations.h"
#include "../Input/Mouse.h"
#include "../Input/Keyboard.h"
#include "../Input/KeyboardBinding.h"
#include "../Input/Binding.h"
#include "../Input/KeyConfig/Config.h"
#include "../StringOperations/Operations.h"

const std::string KEY_CONFIG_FILE_NAME = "keyconfig.ini";

using namespace DivaHook::Input;
using namespace DivaHook::Input::KeyConfig;
using namespace DivaHook::StringOperations;

namespace fs = std::filesystem;

namespace DivaHook::Components
{
	Binding* TestBinding;
	Binding* ServiceBinding;

	Binding* StartBinding;
	Binding* SankakuBinding;
	Binding* ShikakuBinding;
	Binding* BatsuBinding;
	Binding* MaruBinding;

	Binding* LeftBinding;
	Binding* RightBinding;

	JvsEmulator::JvsEmulator()
	{
	}

	JvsEmulator::~JvsEmulator()
	{
		delete TestBinding;
		delete ServiceBinding;
		delete StartBinding;
		delete SankakuBinding;
		delete ShikakuBinding;
		delete BatsuBinding;
		delete MaruBinding;
		delete LeftBinding;
		delete RightBinding;

		Config::Keymap.clear();
	}

	void JvsEmulator::Initialize()
	{
		jvsState = GetJvsStatePtr(JVS_STATE_PTR_ADDRESS);

		//printf("JvsEmulator::Initialize(): Test\n");

		TestBinding = new Binding();
		ServiceBinding = new Binding();
		StartBinding = new Binding();

		SankakuBinding = new Binding();
		ShikakuBinding = new Binding();
		BatsuBinding = new Binding();
		MaruBinding = new Binding();

		LeftBinding = new Binding();
		RightBinding = new Binding();

		std::unordered_map<std::string, std::string> keyconfig;

		CHAR modulePathBuffer[MAX_PATH];
		if (GetModuleFileNameA(MainModule::Module, modulePathBuffer, MAX_PATH))
		{
			fs::path modulePath(modulePathBuffer);
			fs::path configPath = modulePath.parent_path() / KEY_CONFIG_FILE_NAME;

			//printf("KeyConfig path = %s\n", configPath.string().c_str());

			if (fs::exists(configPath))
			{
				std::ifstream configfile(configPath.string().c_str());
				if (configfile.is_open())
				{
					std::string line;
					while (std::getline(configfile, line))
					{
						if (line[0] == '#') continue;
						auto splitline = Split(line, "=");
						Trim(splitline[0]);
						Trim(splitline[1]);
						keyconfig.insert(std::make_pair(splitline[0], splitline[1]));
					}
					configfile.close();
				}
			}
		}

		auto BindConfigKeys = [&](const char* configKeyName, Binding& bindObj, std::vector<std::string> defaultKeys)->void
		{
			std::vector<std::string> keys;
			auto conf = keyconfig.find(configKeyName);

			if (conf != keyconfig.end()) // config variable was found in the ini
			{
				keys = Split(conf->second, ",");
			}
			else
			{ 
				keys = defaultKeys; 
			}

			for (std::string key : keys)
			{
				Trim(key);
				// Applies only for Single-Character keys
				if (key.length() == 1) 
				{
					bindObj.AddBinding(new KeyboardBinding(key[0])); 
				}
				else // for special key names
				{
					auto keycode = Config::Keymap.find(key.c_str());
					if (keycode != Config::Keymap.end()) // name is known in the special keys map
					{
						bindObj.AddBinding(new KeyboardBinding(keycode->second));
					} 
					//else { printf("Bad key name!? Key: %s", key.c_str()); }
				}
			}
		};

		BindConfigKeys("JVS_TEST", *TestBinding, { "F1" });
		BindConfigKeys("JVS_SERVICE", *ServiceBinding, { "F2" });
		BindConfigKeys("JVS_START", *StartBinding, { "Enter" });
		BindConfigKeys("JVS_TRIANGLE", *SankakuBinding, { "W", "I" });
		BindConfigKeys("JVS_SQUARE", *ShikakuBinding, { "A", "J" });
		BindConfigKeys("JVS_CROSS", *BatsuBinding, { "S", "K" });
		BindConfigKeys("JVS_CIRCLE", *MaruBinding, { "D", "L" });
		BindConfigKeys("JVS_LEFT", *LeftBinding, { "Q", "U" });
		BindConfigKeys("JVS_RIGHT", *RightBinding, { "E", "O" });
	}

	void JvsEmulator::Update()
	{
		// to reset the button state once focus is lost
		jvsState->TappedState = JVS_NONE;
		jvsState->DownState = JVS_NONE;
	}

	void JvsEmulator::UpdateInput()
	{
		jvsState->TappedState = GetJvsTappedState();
		jvsState->DownState = GetJvsDownState();

		// repress held down buttons to not block input
		jvsState->DownState ^= jvsState->TappedState;
	}

	JvsState* JvsEmulator::GetJvsStatePtr(int address)
	{
		return (JvsState*)(*(int*)address);
	}

	JvsButtons JvsEmulator::GetJvsTappedState()
	{
		JvsButtons buttons = JVS_NONE;

		if (TestBinding->AnyTapped())
			buttons |= JVS_TEST;
		if (ServiceBinding->AnyTapped())
			buttons |= JVS_SERVICE;

		if (StartBinding->AnyTapped())
			buttons |= JVS_START;

		if (SankakuBinding->AnyTapped())
			buttons |= JVS_TRIANGLE;
		if (ShikakuBinding->AnyTapped())
			buttons |= JVS_SQUARE;
		if (BatsuBinding->AnyTapped())
			buttons |= JVS_CROSS;
		if (MaruBinding->AnyTapped())
			buttons |= JVS_CIRCLE;

		if (LeftBinding->AnyTapped())
			buttons |= JVS_L;
		if (RightBinding->AnyTapped())
			buttons |= JVS_R;

		return buttons;
	}

	JvsButtons JvsEmulator::GetJvsDownState()
	{
		JvsButtons buttons = JVS_NONE;

		if (TestBinding->AnyDown())
			buttons |= JVS_TEST;
		if (ServiceBinding->AnyDown())
			buttons |= JVS_SERVICE;

		if (StartBinding->AnyDown())
			buttons |= JVS_START;

		if (SankakuBinding->AnyDown())
			buttons |= JVS_TRIANGLE;
		if (ShikakuBinding->AnyDown())
			buttons |= JVS_SQUARE;
		if (BatsuBinding->AnyDown())
			buttons |= JVS_CROSS;
		if (MaruBinding->AnyDown())
			buttons |= JVS_CIRCLE;

		if (LeftBinding->AnyDown())
			buttons |= JVS_L;
		if (RightBinding->AnyDown())
			buttons |= JVS_R;

		return buttons;
	}
}
