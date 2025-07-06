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

private:
    Menu() = default;

    std::map<std::string, PatchCheat> patchCheats;
    bool isFallingSpeed{ false };
    bool isWalkingSpeed{ false };
    bool isWallClimb{ false };
    bool isGravityJump{ false };
    float walkingSpeed{ Base::Default::walkingSpeed };
    float jumpGravity{ Base::Default::jumpGravity };
};