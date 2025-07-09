#include "pch.h"
#include "entityManager.h"
#include "base.h"
#include "player.h"

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

void EntityManager::Update()
{
    currentEntity = *(uintptr_t*)(*Ptr::entityManager + firstEntity);
    ImDrawList* drawList = ImGui::GetForegroundDrawList();

    ImGuiIO& io = ImGui::GetIO();
    ImVec2 topCenter = ImVec2(io.DisplaySize.x / 2, 0.f);

    while (currentEntity != NULL && (currentEntity & 1) == 0) {
        int type = *(int*)(currentEntity + 0x14);
        if (type == UNIT && type != PLAYER)
        {
            float x = *(float*)(currentEntity + 0x9A8 + 0x10);
            float y = *(float*)(currentEntity + 0x9A8 + 0x14);
            float z = *(float*)(currentEntity + 0x9A8 + 0x18);

            Vec3 enemyPos = { x, y, z };

            auto& player = Player::Get();
            Vec3 playerPos = { player.getX(), player.getY(), player.getZ() };

            float dist = Utils::Distance(playerPos, enemyPos);
            if (dist < 50.f)
            {
                ImVec2 screenPos;
                if (WorldToScreenInternal(enemyPos, screenPos))
                {
                    drawList->AddLine(topCenter, screenPos, IM_COL32(0, 255, 0, 255), 0.5f);
                }
            }
        }

        currentEntity = *(uintptr_t*)(currentEntity + nextEntity);
    }
}