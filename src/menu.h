#pragma once
#include "player.h"
#include "base.h"

namespace Menu
{
    extern bool isFallingSpeed;
    extern bool isWalkingSpeed;
    extern bool isWallClimb;
    extern bool isInfiniteJump;
    extern bool isNoFallDamage;
    extern bool isAirSwim;
    extern float walkingSpeed;

    void Show();
    void ExecuteOptions();
}