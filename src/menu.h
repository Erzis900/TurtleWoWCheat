#pragma once
#include "player.h"
#include "base.h"
#include <map>

struct PatchCheat 
{
    bool checkboxState;
    bool patchState;
    size_t patchSize;
    std::vector<BYTE> originalBytes;
    std::vector<BYTE> patchBytes;
    DWORD address;
};

class Menu
{
public:
    static Menu& Get();
    void Show();
    void ExecuteOptions();
    void initializePatchCheats();

    std::map<std::string, PatchCheat> patchCheats;
    bool isFallingSpeed{false};
    bool isWalkingSpeed{false};
    bool isWallClimb{false};
    float walkingSpeed{Base::Default::walkingSpeed};

protected:
    Menu() = default;
};