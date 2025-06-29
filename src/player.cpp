#include "pch.h"#
#include "player.hpp"
#include "base.h"

namespace Player
{
	float* y = (float*)(Base::Addr::player + 0x14);
	float* z = (float*)(Base::Addr::player + 0x18);
	float* x = (float*)(Base::Addr::player + 0x10);
	float* walkingSpeed = (float*)(Base::Addr::player + 0x84);
	float* fallingSpeed = (float*)0x0087D894;

    void SetWalkingSpeed(float speed)
    {
        *walkingSpeed = speed;
    }

    float GetWalkingSpeed()
    {
        return *walkingSpeed;
    }

	void SetFailingSpeed(float speed)
	{
		*fallingSpeed = speed;
	}

	float GetFailingSpeed()
	{
		return *fallingSpeed;
	}
};