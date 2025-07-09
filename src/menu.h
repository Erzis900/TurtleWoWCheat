#pragma once
#include "player.h"
#include "base.h"
#include <functional>
#include <map>

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

private:
    Menu() = default;

    std::map<std::string, ValueCheat> valueCheats;
    std::map<std::string, PatchCheat> patchCheats;
};