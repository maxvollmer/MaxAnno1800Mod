
#include "pch.h"
#include "UUIDHelper.h"

// Code for generating UUID taken from here: https://lowrey.me/guid-generation-in-c-11/

#include <vector>
#include <iostream>
#include <sstream>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>
#include <string>

using namespace MaxAnno1800Mod;

std::string UUIDHelper::GetRandomUUID()
{
	std::stringstream uuid;
	uuid << GenerateHexString(4);
	uuid << '-';
	uuid << GenerateHexString(2);
	uuid << '-';
	uuid << GenerateHexString(2);
	uuid << '-';
	uuid << GenerateHexString(2);
	uuid << '-';
	uuid << GenerateHexString(6);
	return uuid.str();
}

unsigned char UUIDHelper::RandomChar()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 255);
	return static_cast<unsigned char>(dis(gen));
}

std::string UUIDHelper::GenerateHexString(const unsigned int len)
{
	std::stringstream ss;
	for (unsigned int i = 0; i < len; i++)
	{
		auto rc = RandomChar();
		std::stringstream hexstream;
		hexstream << std::hex << int(rc);
		auto hex = hexstream.str();
		ss << (hex.length() < 2 ? '0' + hex : hex);
	}
	return ss.str();
}
