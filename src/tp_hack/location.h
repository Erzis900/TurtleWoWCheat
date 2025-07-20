#pragma once
#include <string>
#include <tuple>

class Location
{
public:
    Location(const std::string& name, float x, float y, float z)
        : name(name), x(x), y(y), z(z) {}

    const float x, y, z;
    const std::string name;
};