#pragma once
#include "pch.h"
#include "base.h"
#include "tp_hack/locationProvider.h"
#include "player.h"
#include <functional>
#include <map>
#include "tp_hack/location.h"

struct ValueCheat
{
    bool checkboxState; // state in GUI
    bool isActivated; // state in game
    const bool showSlider;
    std::function<void(float)> handler;
    float valueController; // to be modified by slider, if showSlider is set to true
    const float defaultValueWhenOff; // original value
    const float minValue;
    const float maxValue;
};

struct PatchCheat
{
    bool checkboxState;
    bool isActivated;
    size_t patchSize;
    std::vector<BYTE> originalBytes;
    std::vector<BYTE> patchBytes;
    uintptr_t address;
};

class Menu
{
public:
    static Menu& Get();
    void Show();
    void ExecuteOptions();
    void initializeValueCheats();
    void initializePatchCheats();

    bool getIsESP() { return isESP; }

private:
    Menu() = default;

    std::map<std::string, ValueCheat> valueCheats{};
    std::map<std::string, PatchCheat> patchCheats{};
    LocationProvider locationProvider{};
    LocationProvider::LocationsMap locationsMap;

    // custom teleport
    char locationName[128] = "";
    std::vector<Location> savedLocations;
    int selectedLocationIndex = -1;

    bool isESP{ false };
};