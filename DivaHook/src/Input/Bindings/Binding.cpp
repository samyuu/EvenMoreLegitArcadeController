#include "Binding.h"

namespace DivaHook::Input
{
	Binding::Binding()
	{
	}

	Binding::~Binding()
	{
		for (auto& binding : InputBindings)
			delete binding;
	}

	void Binding::AddBinding(IInputBinding* inputBinding)
	{
		InputBindings.push_back(inputBinding);
	}

	bool Binding::AnyDown()
	{
		for (auto& binding : InputBindings)
		{
			if (binding->IsDown())
				return true;
		}

		return false;
	}

	bool Binding::AnyTapped()
	{
		for (auto& binding : InputBindings)
		{
			if (binding->IsTapped())
				return true;
		}

		return false;
	}

	bool Binding::AnyReleased()
	{
		for (auto& binding : InputBindings)
		{
			if (binding->IsReleased())
				return true;
		}

		return false;
	}
}
