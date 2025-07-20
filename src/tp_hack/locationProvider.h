#pragma once
#include "pch.h"
#include <filesystem>
#include <functional>
#include <map>
#include <vector>
#include "location.h"

enum class LocationCategory : uint8_t
{
    Misc,
    Cities,
    Dungeons,
    First = Misc,
    Last = Dungeons
};

inline static std::string string(LocationCategory category)
{
    static const std::unordered_map<LocationCategory, std::string> categoryNames = {
        {LocationCategory::Misc, "Misc"},
        {LocationCategory::Cities, "Cities"},
        {LocationCategory::Dungeons, "Dungeons"}
    };
    return categoryNames.at(category);
}

enum class Land : uint8_t
{
    Kalimdor,
    EasternKingdoms,
    // Outland,
    First = Kalimdor,
    Last = EasternKingdoms
};

inline static std::string string(Land land)
{
    static const std::unordered_map<Land, std::string> landNames = {
        {Land::Kalimdor, "Kalimdor"},
        {Land::EasternKingdoms, "Eastern Kingdoms"},
        // {Land::Outland, "Outland"}
    };
    return landNames.at(land);
}

class LocationProvider
{
public:
    template<typename T>
    using MapToLocations = std::unordered_map<T, std::vector<Location>>;
    using LocationsMap = std::unordered_map<Land, MapToLocations<LocationCategory>>;

    LocationProvider();

    void ForAllLocations(const std::function<void(const Location&)>& callback) const;
    
    std::vector<Location> GetLocations(Land land, LocationCategory category) const;

    std::vector<std::tuple<Land, LocationCategory, Location>> GetAllLocations() const;

    LocationsMap GetLocationsMap() const;
private:
    LocationsMap locations;
};