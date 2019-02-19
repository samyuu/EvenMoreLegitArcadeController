#pragma once
#include <functional>
#include <Windows.h>
#include "EmulatorComponent.h"
#include "JvsState.h"
#include "../Input/Binding.h"

namespace DivaHook::Components
{
	class JvsEmulator : public EmulatorComponent
	{
		const int JVS_STATE_PTR_ADDRESS = 0x00F05D84;

	public:
		JvsEmulator();
		~JvsEmulator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void UpdateInput() override;

	private:
		JvsState* jvsState;
		JvsState* GetJvsStatePtr(int address);

		JvsButtons GetJvsTappedState();
		JvsButtons GetJvsDownState();
	};
}

