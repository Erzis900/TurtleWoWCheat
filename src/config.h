#pragma once
#include <string>
#include <json.hpp>

using json = nlohmann::json;

namespace Config
{
	extern json settings;
	extern std::string path;
	extern bool isUpdated;

	void Load();
	void Save();
};