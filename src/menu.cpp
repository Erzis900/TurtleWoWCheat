#include "pch.h"
#include "menu.h"

namespace Menu
{
	bool isFallingSpeed = false;
	bool isWalkingSpeed = false;
	bool isWallClimb = false;

    void ExecuteOptions()
    {
        Player::SetFailingSpeed(isFallingSpeed ? 3.f : Base::Default::fallingSpeed);
        if(!isWalkingSpeed) Player::SetWalkingSpeed(Base::Default::walkingSpeed);
    }
}