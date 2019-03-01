#include <iostream>
#include "windows.h"
#include "InputEmulator.h"
#include <fstream>
#include <algorithm>
#include <filesystem>
#include "../Constants.h"
#include "../MainModule.h"
#include "../Input/Mouse.h"
#include "../Input/Keyboard.h"
#include "../Input/KeyboardBinding.h"
#include "../Input/Binding.h"
#include "../Input/KeyConfig/Config.h"
#include "../Utilities/Operations.h"
#include "../Utilities/EnumBitwiseOperations.h"

const std::string KEY_CONFIG_FILE_NAME = "keyconfig.ini";

using namespace DivaHook::Input;
using namespace DivaHook::Input::KeyConfig;
using namespace DivaHook::Utilities;

namespace fs = std::filesystem;

namespace DivaHook::Components
{
	InputEmulator::InputEmulator()
	{
	}

	InputEmulator::~InputEmulator()
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

	void InputEmulator::Initialize()
	{
		inputState = GetInputStatePtr(INPUT_STATE_PTR_ADDRESS);

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

	void InputEmulator::Update()
	{
		return;
	}

	void InputEmulator::OnFocusLost()
	{
		// to prevent buttons from being "stuck"
		inputState->ClearState();
	}

	void InputEmulator::UpdateInput()
	{
		auto tappedFunc = [](void* binding) { return ((Binding*)binding)->AnyTapped(); };
		auto releasedFunc = [](void* binding) { return ((Binding*)binding)->AnyReleased(); };
		auto downFunc = [](void* binding) { return ((Binding*)binding)->AnyDown(); };
		auto doubleTapFunc = [](void* binding) { return ((Binding*)binding)->AnyDoubleTapped(); };

		inputState->Tapped.Buttons = GetJvsButtonsState(tappedFunc);
		inputState->Released.Buttons = GetJvsButtonsState(releasedFunc);
		inputState->Down.Buttons = GetJvsButtonsState(downFunc);
		inputState->DoubleTapped.Buttons = GetJvsButtonsState(doubleTapFunc);

		// repress held down buttons to not block input
		inputState->Down.Buttons ^= inputState->Tapped.Buttons;

		auto mouse = Mouse::GetInstance();

		auto pos = mouse->GetRelativePosition();
		inputState->MouseX = (int)pos.x;
		inputState->MouseY = (int)pos.y;

		auto deltaPos = mouse->GetDeltaPosition();
		inputState->MouseDeltaX = (int)deltaPos.x;
		inputState->MouseDeltaY = (int)deltaPos.y;

		UpdateInputBit(5, VK_LEFT);
		UpdateInputBit(6, VK_RIGHT);

		UpdateInputBit(39, 'A');
		UpdateInputBit(55, 'Q');
		UpdateInputBit(57, 'S'); // unsure
		UpdateInputBit(61, 'W');
		UpdateInputBit(63, 'Y');
		UpdateInputBit(84, 'L'); // unsure
		
		UpdateInputBit(80, VK_RETURN);
		UpdateInputBit(91, VK_UP);
		UpdateInputBit(93, VK_DOWN);
		
		UpdateInputBit(96, MK_LBUTTON);
		UpdateInputBit(97, VK_MBUTTON);
		UpdateInputBit(98, MK_RBUTTON);
	}

	InputState* InputEmulator::GetInputStatePtr(int address)
	{
		return (InputState*)(*(int*)address);
	}

	JvsButtons InputEmulator::GetJvsButtonsState(bool(*buttonTestFunc)(void*))
	{
		JvsButtons buttons = JVS_NONE;

		if (buttonTestFunc(TestBinding))
			buttons |= JVS_TEST;
		if (buttonTestFunc(ServiceBinding))
			buttons |= JVS_SERVICE;

		if (buttonTestFunc(StartBinding))
			buttons |= JVS_START;

		if (buttonTestFunc(SankakuBinding))
			buttons |= JVS_TRIANGLE;
		if (buttonTestFunc(ShikakuBinding))
			buttons |= JVS_SQUARE;
		if (buttonTestFunc(BatsuBinding))
			buttons |= JVS_CROSS;
		if (buttonTestFunc(MaruBinding))
			buttons |= JVS_CIRCLE;

		if (buttonTestFunc(LeftBinding))
			buttons |= JVS_L;
		if (buttonTestFunc(RightBinding))
			buttons |= JVS_R;

		return buttons;
	}

	void InputEmulator::UpdateInputBit(uint32_t bit, uint8_t keycode) 
	{
		auto keyboard = Keyboard::GetInstance();

		inputState->SetBit(bit, keyboard->IsTapped(keycode), INPUT_TAPPED);
		inputState->SetBit(bit, keyboard->IsReleased(keycode), INPUT_RELEASED);
		inputState->SetBit(bit, keyboard->IsDown(keycode), INPUT_DOWN);
		inputState->SetBit(bit, keyboard->IsDoubleTapped(keycode), INPUT_DOUBLE_TAPPED);
	}
}
