#pragma once

#include <unordered_map>
#include "KeyString.h"
#include "KeyStringHash.h"
#include "../Bindings/Binding.h"

namespace DivaHook::Input::KeyConfig
{
	typedef std::unordered_map<KeyString, uint8_t, KeyStringHash> KeycodeMap;

	class Config
	{
	public:
		static KeycodeMap Keymap;

		static void BindConfigKeys(std::unordered_map<std::string, std::string> &configMap, const char *configKeyName, Binding &bindObj, std::vector<std::string> defaultKeys);
	};
}
