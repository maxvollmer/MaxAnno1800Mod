#pragma once

#include <string>
#include "Constants.h"

namespace MaxAnno1800Mod
{
	class InputHelper
	{
	public:

		static bool GetYesNoResponse(const std::string& prompt);

		static ModAction PromptModAction();

	private:
		static void PrintModActionPrompt();

	};
}
