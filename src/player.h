#pragma once
#include "utils.h"

class Player
{
    template<typename T>
    using Protected = Utils::Protected<T>;
public:
    static Player& Get();

    float getX() const { return *xAddr; }
    float getY() const { return *yAddr; }
    float getZ() const { return *zAddr; }
	void setX(float x) { xAddr = x; }
	void setY(float y) { yAddr = y; }
	void setZ(float z) { zAddr = z; }

    float getWalkingSpeed() const { return *walkingSpeedAddr; }
    float getFallingSpeed() const { return *fallingSpeedAddr; }
    float getWallClimb() const { return *wallClimbAddr; }
    void setWalkingSpeed(float speed) { walkingSpeedAddr = speed; }
    void setFallingSpeed(float speed) { fallingSpeedAddr = speed; }
    void setWallClimb(float value) { wallClimbAddr = value; }
    void setJumpGravity(float value) { gravityJumpAddr = value; }

private:
    static const std::ptrdiff_t walkingSpeedOffset = 0x84;
    static const std::vector<int> playerAddrOffsets;
    static const ptrdiff_t playerPosOffsets[3];
    Protected<float> fallingSpeedAddr{ reinterpret_cast<float*>(0x0087D894) };
    Protected<float> wallClimbAddr{ reinterpret_cast<float*>(0x0080DFFC) };
    Protected<float> gravityJumpAddr{ reinterpret_cast<float*>(0x007C6272) };
    uintptr_t playerAddr;
    Protected<float> xAddr;
    Protected<float> yAddr;
    Protected<float> zAddr;
    Protected<float> walkingSpeedAddr;

    Player();
    Player(Player&&) = default;
    Player& operator=(Player&&) = default;
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    ~Player() = default;
};
