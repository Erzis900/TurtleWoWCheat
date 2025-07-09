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

void EntityManager::DrawESPLine(const ImVec2& from, const ImVec2& to)
{
    ImDrawList* drawList = ImGui::GetForegroundDrawList();
    drawList->AddLine(from, to, GetImGuiColor(color), 0.5f);
}

void EntityManager::DrawESPText(const ImVec2& to, float distance)
{
    ImDrawList* drawList = ImGui::GetForegroundDrawList();
    drawList->AddText(to, GetImGuiColor(color), std::to_string(distance).c_str());
}

ImU32 EntityManager::GetImGuiColor(float* color)
{
    return IM_COL32(color[0] * 255, color[1] * 255, color[2] * 255, 255);
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
            float distance = Utils::Distance(playerPos, enemyPos);

            if (!isDistanceLimit || distance < maxDistance)
            {
                ImVec2 fromScreen, toScreen;
                if (WorldToScreenInternal(playerPos, fromScreen) && WorldToScreenInternal(enemyPos, toScreen))
                {
                    DrawESPLine(fromScreen, toScreen);
                    DrawESPText(toScreen, distance);
                }
            }
        }

        currentEntity = *(uintptr_t*)(currentEntity + nextEntity);
    }
}