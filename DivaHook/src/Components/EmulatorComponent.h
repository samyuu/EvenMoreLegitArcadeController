#pragma once

namespace DivaHook::Components
{
	class EmulatorComponent
	{
	public:
		EmulatorComponent();
		~EmulatorComponent();

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void UpdateInput() = 0;

		virtual void OnFocusGain() {};
		virtual void OnFocusLost() {};
	};
}
