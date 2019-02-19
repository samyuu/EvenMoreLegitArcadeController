#pragma once
#include <unordered_map>
#include "KeyString.h"
#include "KeyStringHash.h"

namespace DivaHook::Input::KeyConfig
{
	typedef std::unordered_map<KeyString, uint8_t, KeyStringHash> KeycodeMap;

	class Config
	{
	public:
		static KeycodeMap Keymap;
	};
}
