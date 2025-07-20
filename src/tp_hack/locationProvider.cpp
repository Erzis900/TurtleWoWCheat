#include "pch.h"
#include "locationProvider.h"

LocationProvider::LocationsMap initLocations();

LocationProvider::LocationProvider()
    : locations{initLocations()}
{
}

void LocationProvider::ForAllLocations(const std::function<void(const Location&)>& callback) const
{
    for (const auto& [land, categories] : locations)
    {
        for (const auto& [category, locs] : categories)
        {
            for (const auto& loc : locs)
            {
                callback(loc);
            }
        }
    }
}

std::vector<Location> LocationProvider::GetLocations(Land land, LocationCategory category) const
{
    return locations.at(land).at(category);
}

LocationProvider::LocationsMap LocationProvider::GetLocationsMap() const
{
    return locations;
}

std::vector<std::tuple<Land, LocationCategory, Location>> LocationProvider::GetAllLocations() const
{
    std::vector<std::tuple<Land, LocationCategory, Location>> allLocations;
    for(auto land = Land::First; land <= Land::Last; land = static_cast<Land>(static_cast<uint8_t>(land) + 1))
    {
        for(auto category = LocationCategory::First; category <= LocationCategory::Last; 
            category = static_cast<LocationCategory>(static_cast<uint8_t>(category) + 1))
        {
            auto locations = GetLocations(land, category);
            for(const auto& loc : locations)
            {
                allLocations.emplace_back(land, category, loc);
            }
        }
    }
    return allLocations;
}

static LocationProvider::LocationsMap initLocations()
{
    struct LocationData
    {
        Land land;
        LocationCategory category;
        Location location;
    };

    std::vector<LocationData> data = {
        {Land::Kalimdor, LocationCategory::Misc, Location("Ratchet", -985.70f, -3827.08f, 5.65f)},
        {Land::Kalimdor, LocationCategory::Misc, Location("GM Island", 16224.22f, 16284.02f, 13.18f)},
        {Land::Kalimdor, LocationCategory::Cities, Location("Orgrimmar", 1638.76f, -4449.96f, 15.41f)},
        {Land::Kalimdor, LocationCategory::Cities, Location("Thunderbluff", -1116.07f, 45.23f, 140.81f)},
        {Land::Kalimdor, LocationCategory::Cities, Location("Darnassus", 9959.42f, 2484.32f, 1316.05f)},
        {Land::Kalimdor, LocationCategory::Dungeons, Location("Ragefire Chasm", 1816.08f, -4420.26f, -19.10f)},
        {Land::Kalimdor, LocationCategory::Dungeons, Location("Wailing Caverns", -740.49f, -2216.32f, 16.14f)},
        {Land::Kalimdor, LocationCategory::Dungeons, Location("Blackfathom Deeps", 4247.26f, 742.95f, -24.86f)},
        {Land::Kalimdor, LocationCategory::Dungeons, Location("Razorfen Kraul", -4463.15f, -1664.81f, 82.30f)},
        {Land::Kalimdor, LocationCategory::Dungeons, Location("Razorfen Downs", -4659.02f, -2526.55f, 81.52f)},
        {Land::Kalimdor, LocationCategory::Dungeons, Location("Zul'Farrak", -6798.37f, -2889.57f, 8.89f)},
        {Land::Kalimdor, LocationCategory::Dungeons, Location("Maraudon", -1183.55f, 2875.33f, 85.83f)},
        {Land::Kalimdor, LocationCategory::Dungeons, Location("Dire Maul", -4430.82f, 1409.87f, 132.46f)},
        {Land::Kalimdor, LocationCategory::Dungeons, Location("Mystical Grove", 1700.44f, -1274.55f, 161.05f)},
        {Land::Kalimdor, LocationCategory::Dungeons, Location("Caverns of Time", -8511.12f, -4471.97f, -213.57f)},
        {Land::EasternKingdoms, LocationCategory::Misc, Location("Booty Bay", -14283.87f, 559.34f, 8.75f)},
        {Land::EasternKingdoms, LocationCategory::Cities, Location("Stormwind", -8866.26f, 671.65f, 97.90f)},
        {Land::EasternKingdoms, LocationCategory::Cities, Location("Ironforge", -5025.98f, -828.38f, 495.31f)},
        {Land::EasternKingdoms, LocationCategory::Cities, Location("Alah'Thalas", 4326.88f, -2877.66f, 7.77f)},
        {Land::EasternKingdoms, LocationCategory::Cities, Location("Undercity", 1747.82f, 238.60f, 61.69f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Deadmines", -11208.30f, 1676.07f, 24.57f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Shadowfang Keep", -232.12f, 1569.22f, 76.89f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Gnomeregan", -5163.39f, 927.85f, 257.18f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Scarlet Monastery", 2916.29f, -823.17f, 160.33f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Stockade", -8766.18f, 845.09f, 88.11f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Uldaman", -6066.52f, -2955.38f, 209.77f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Atal'Dazar", -10175.55f, -3994.99f, -112.50f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Blackrock Spire", -7524.45f, -1229.70f, 285.73f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Blackrock Depths", -7180.81f, -921.72f, 165.90f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Scholomance", 1275.30f, -2552.72f, 89.83f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Stratholme Main", 3392.84f, -3356.15f, 142.25f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Stratholme Back", 3234.26f, -4049.72f, 108.45f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Hateforge Quarry", -8171.47f, -3109.18f, 200.46f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Karazhan Crypts", -11068.31f, -1816.02f, 55.14f)},
        {Land::EasternKingdoms, LocationCategory::Dungeons, Location("Stormwind Vault", -8677.95f, 637.58f, 96.98f)}
    };

    using LocationsMapElement = LocationProvider::LocationsMap::value_type;
    
    const std::unordered_map<LocationCategory, std::vector<Location>> emptyCategoryToVectorMapping{
        {LocationCategory::Misc, {}},
        {LocationCategory::Cities, {}},
        {LocationCategory::Dungeons, {}}
    };

    LocationProvider::LocationsMap locations{
        {Land::Kalimdor, emptyCategoryToVectorMapping},
        {Land::EasternKingdoms, emptyCategoryToVectorMapping},
        // {Land::Outland, emptyCategoryToVectorMapping}
    };

    for (const auto& entry : data)
    {
        locations[entry.land][entry.category].emplace_back(entry.location);
    }

    return locations; 
}