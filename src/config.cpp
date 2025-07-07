#include "pch.h"
#include "config.h"
#include <fstream>
#include <spdlog/spdlog.h>
#include "base.h"

namespace Config
{
    json settings;
    std::string path = "config.json";
    bool isUpdated = false;

    void Load()
    {
        std::ifstream f(path);
        if (!f.is_open())
        {
            spdlog::error(path + " not found");
            Base::Data::ToDetach = true;
            return;
        }

        spdlog::info(path + " loaded");

        settings = json::parse(f);
    }

    void Save()
    {
        std::ofstream file(path);
        file << settings.dump(4);
    }
};
