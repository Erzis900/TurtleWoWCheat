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
    : playerAddr(Utils::ResolveChain(Base::Addr::base + Base::Offset::player, { 0x5C, 0x9A8 })), // TODO fix offsets argument passing
      xAddr(reinterpret_cast<float*>(playerAddr + playerPosOffsets[0])),
      yAddr(reinterpret_cast<float*>(playerAddr + playerPosOffsets[1])),
      zAddr(reinterpret_cast<float*>(playerAddr + playerPosOffsets[2])),
      walkingSpeedAddr(reinterpret_cast<float*>(playerAddr + 0x84)) // TODO fix offsets argument passing
{}