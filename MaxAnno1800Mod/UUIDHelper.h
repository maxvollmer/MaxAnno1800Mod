#pragma once

#include <string>

namespace MaxAnno1800Mod
{
	class UUIDHelper
	{
	public:
		static std::string GetRandomUUID();

	private:
		static unsigned char RandomChar();
		static std::string GenerateHexString(const unsigned int len);

	};
}
