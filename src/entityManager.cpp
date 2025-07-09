#include "pch.h"
#include "entityManager.h"
#include "player.h"
#include <limits>

bool WorldToScreenInternal(Vec3 pos, ImVec2& screenOut)
{
    uintptr_t worldFrame = *Ptr::worldFrame;
    if (!worldFrame)
        return false;

    ImVec2 raw;
    if (!Ptr::WorldToScreen(worldFrame, &pos, &raw))
        return false;

    // TODO fix magic values
    ImGuiIO& io = ImGui::GetIO();
    screenOut.x = raw.x / 0.8715755343f * io.DisplaySize.x;
    screenOut.y = io.DisplaySize.y - raw.y / 0.4902612269f * io.DisplaySize.y;

    return true;
}

EntityManager& EntityManager::Get()
{
    static EntityManager instance;
    return instance;
}

EntityManager::EntityManager()
{
    firstEntity = 0xAC;
    nextEntity = 0x3C;
}

bool EntityManager::IsValidEntity(uintptr_t entity) const
{
    int type = *(int*)(entity + 0x14);
    return (type == UNIT && type != PLAYER);
}

Vec3 EntityManager::GetEntityPos(uintptr_t entity) const
{
    float x = *(float*)(currentEntity + 0x9A8 + 0x10);
    float y = *(float*)(currentEntity + 0x9A8 + 0x14);
    float z = *(float*)(currentEntity + 0x9A8 + 0x18);

    return { x, y, z };
}

void EntityManager::DrawLine(const Vec3& from, const Vec3& to)
{
    ImVec2 screenPos;
    if (!WorldToScreenInternal(to, screenPos))
        return;

    ImDrawList* drawList = ImGui::GetForegroundDrawList();
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 topCenter = ImVec2(io.DisplaySize.x / 2, 0.f);

    drawList->AddLine(topCenter, screenPos, IM_COL32(0, 255, 0, 255), 0.5f);
}

void EntityManager::Update()
{
    currentEntity = *(uintptr_t*)(*Ptr::entityManager + firstEntity);

    auto& player = Player::Get();
    Vec3 playerPos = { player.getX(), player.getY(), player.getZ() };

    while (currentEntity != NULL && (currentEntity & 1) == 0) {
        if (IsValidEntity(currentEntity))
        {
            Vec3 enemyPos = GetEntityPos(currentEntity);
            if (!isDistanceLimit || Utils::Distance(playerPos, enemyPos) < maxDistance)
            {
                DrawLine(playerPos, enemyPos);
            }
        }

        currentEntity = *(uintptr_t*)(currentEntity + nextEntity);
    }
}