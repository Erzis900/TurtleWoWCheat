#include "pch.h"
#include "player.h"
#include "utils.h"
#include "base.h"

const std::vector<int> Player::playerAddrOffsets{ 0x5C, 0x9A8 };
const int Player::playerPosOffsets[3] = { 0x10, 0x14, 0x18 };

Player& Player::Get()
{
    static Player instance;
    return instance;
}

Player::Player()
    : playerAddr(Utils::ResolveChain(Base::Addr::base + Base::Offset::player, playerAddrOffsets)),
      xAddr(reinterpret_cast<float*>(playerAddr + playerPosOffsets[0])),
      yAddr(reinterpret_cast<float*>(playerAddr + playerPosOffsets[1])),
      zAddr(reinterpret_cast<float*>(playerAddr + playerPosOffsets[2])),
      walkingSpeedAddr(reinterpret_cast<float*>(playerAddr + walkingSpeedOffset))
{
}