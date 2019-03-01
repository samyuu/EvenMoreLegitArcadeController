#include "Config.h"
#include "windows.h"
#include "../KeyboardBinding.h"
#include "../../Utilities/Operations.h"

namespace DivaHook::Input::KeyConfig
{
	KeycodeMap Config::Keymap =
	{
		// NumPad Keys
		{ "NumPad0", VK_NUMPAD0 },
		{ "NumPad1", VK_NUMPAD1 },
		{ "NumPad2", VK_NUMPAD2 },
		{ "NumPad3", VK_NUMPAD3 },
		{ "NumPad4", VK_NUMPAD4 },
		{ "NumPad5", VK_NUMPAD5 },
		{ "NumPad6", VK_NUMPAD6 },
		{ "NumPad7", VK_NUMPAD7 },
		{ "NumPad8", VK_NUMPAD8 },
		{ "NumPad9", VK_NUMPAD9 },
		{ "Plus", VK_ADD },
		{ "Minus", VK_SUBTRACT },
		{ "Divide", VK_DIVIDE },
		{ "Multiply", VK_MULTIPLY },
		// F-Keys
		{ "F1", VK_F1 },
		{ "F2", VK_F2 },
		{ "F3", VK_F3 },
		{ "F4", VK_F4 },
		{ "F5", VK_F5 },
		{ "F6", VK_F6 },
		{ "F7", VK_F7 },
		{ "F8", VK_F8 },
		{ "F9", VK_F9 },
		{ "F10", VK_F10 },
		{ "F11", VK_F11 },
		{ "F12", VK_F12 },
		{ "F13", VK_F13 },
		{ "F14", VK_F14 },
		{ "F15", VK_F15 },
		{ "F16", VK_F16 },
		{ "F17", VK_F17 },
		{ "F18", VK_F18 },
		{ "F19", VK_F19 },
		{ "F20", VK_F20 },
		{ "F21", VK_F21 },
		{ "F22", VK_F22 },
		{ "F23", VK_F23 },
		{ "F24", VK_F24 },
		// Shift Keys
		{ "LeftShift", VK_LSHIFT },
		{ "LShift",    VK_LSHIFT },
		{ "RightShift", VK_RSHIFT },
		{ "RShift",     VK_RSHIFT },
		// Control Keys
		{ "LeftControl",  VK_LCONTROL },
		{ "LControl",     VK_LCONTROL },
		{ "LCtrl",        VK_LCONTROL },
		{ "RightControl", VK_RCONTROL },
		{ "RControl",     VK_RCONTROL },
		{ "RCtrl",        VK_RCONTROL },
		// Arrow Keys
		{ "Up",    VK_UP },
		{ "Down",  VK_DOWN },
		{ "Left",  VK_LEFT },
		{ "Right", VK_RIGHT },
		// Special Keys
		{ "Enter",  VK_RETURN },
		{ "Return", VK_RETURN },
		{ "Tab",	VK_TAB },
		{ "Back",      VK_BACK },
		{ "Backspace", VK_BACK },
		{ "Insert", VK_INSERT },
		{ "Ins",    VK_INSERT },
		{ "Delete", VK_DELETE },
		{ "Del",    VK_DELETE },
		{ "Home", VK_HOME },
		{ "End",  VK_END },
		{ "PageUp",   VK_PRIOR },
		{ "PageDown", VK_NEXT },
		{ "ESC",    VK_ESCAPE },
		{ "Escape", VK_ESCAPE },
	};

	void Config::BindConfigKeys(std::unordered_map<std::string, std::string> &configMap, const char *configKeyName, Binding &bindObj, std::vector<std::string> defaultKeys)
	{
		std::vector<std::string> keys;

		auto configPair = configMap.find(configKeyName);

		// config variable was found in the ini
		if (configPair != configMap.end())
		{
			keys = Utilities::Split(configPair->second, ",");
		}
		else
		{
			keys = defaultKeys;
		}

		for (std::string key : keys)
		{
			Utilities::Trim(key);

			// Applies only for Single-Character keys
			if (key.length() == 1)
			{
				bindObj.AddBinding(new KeyboardBinding(key[0]));
			}
			else // for special key names
			{
				auto keycode = Config::Keymap.find(key.c_str());

				// name is known in the special keys map
				if (keycode != Config::Keymap.end())
				{
					bindObj.AddBinding(new KeyboardBinding(keycode->second));
				}
				else
				{
					// printf("Bad key name!? Key: %s", key.c_str());
				}
			}
		}
	}
}