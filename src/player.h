#pragma once
namespace Player
{
	extern float* x;
	extern float* y;
	extern float* z;
    extern float* walkingSpeed;
    extern float* fallingSpeed;

    void SetWalkingSpeed(float speed);
    float GetWalkingSpeed();

    void SetFallingSpeed(float speed);
    float GetFallingSpeed();
};
