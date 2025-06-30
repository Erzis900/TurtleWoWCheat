#include "pch.h"
#include "player.h"
#include "utils.h"
#include "base.h"

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