#pragma once

class Player
{
public:
    static Player& Get();

    float& x() { return *xAddr; }
    float& y() { return *yAddr; }
    float& z() { return *zAddr; }
    float x() const { return *xAddr; }
    float y() const { return *yAddr; }
    float z() const { return *zAddr; }

    float& walkingSpeed() { return *walkingSpeedAddr; }
    float& fallingSpeed() { return *fallingSpeedAddr; }
    float walkingSpeed() const { return *walkingSpeedAddr; }
    float fallingSpeed() const { return *fallingSpeedAddr; }

private:
    DWORD playerAddr;
    float* const xAddr;
    float* const yAddr;
    float* const zAddr;
    float* const walkingSpeedAddr;
    inline static const std::vector<DWORD> playerAddrOffsets = { 0x5C, 0x9A8 };
    static constexpr DWORD playerPosOffsets[] = { 0x10, 0x14, 0x18 };
    static constexpr float* fallingSpeedAddr{ reinterpret_cast<float*>(0x0087D894) };
    static constexpr DWORD walkingSpeedOffset = 0x84;

    Player();
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) = delete;
    Player& operator=(Player&&) = delete;
    ~Player() = default;
};
