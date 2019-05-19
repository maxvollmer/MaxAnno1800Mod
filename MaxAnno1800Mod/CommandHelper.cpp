
#include "pch.h"
#include "CommandHelper.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <limits>

using namespace MaxAnno1800Mod;


bool CommandHelper::ExecuteCommand(const std::string& cmd)
{
	STARTUPINFOA si{ 0 };
	si.cb = sizeof(si);

	PROCESS_INFORMATION pi{ 0 };

	if (CreateProcessA(NULL, const_cast<char*>(cmd.data()), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return true;
	}

	return false;
}

