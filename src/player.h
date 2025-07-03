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
    void setWalkingSpeed(float speed) { walkingSpeedAddr = speed; }
    void setFallingSpeed(float speed) { fallingSpeedAddr = speed; }

private:
    DWORD playerAddr;
    Protected<float> xAddr;
    Protected<float> yAddr;
    Protected<float> zAddr;
    Protected<float> walkingSpeedAddr;
    const std::vector<DWORD> playerAddrOffsets = { 0x5C, 0x9A8 };
    const DWORD playerPosOffsets[3] = { 0x10, 0x14, 0x18 };
    Protected<float> fallingSpeedAddr{ reinterpret_cast<float*>(0x0087D894) };
    const DWORD walkingSpeedOffset = 0x84;

    Player();
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) = delete;
    Player& operator=(Player&&) = delete;
    ~Player() = default;
};
