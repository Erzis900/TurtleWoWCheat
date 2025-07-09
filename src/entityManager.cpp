#include "pch.h"
#include "entityManager.h"
#include "base.h"

EntityManager& EntityManager::Get()
{
    static EntityManager instance;
    return instance;
}

EntityManager::EntityManager()
{
    firstEntity = 0xAC;
    nextEntity = 0x3C;

    currentEntity = *(uintptr_t*)(*Ptr::entityManager + firstEntity);
}

void EntityManager::Update()
{
    while (currentEntity != 0 && (currentEntity & 1) == 0) {
        int type = *(int*)(currentEntity + 0x14);
        if (type == 3 || type == 4)
        {
            float x = *(float*)(currentEntity + 0x9A8 + 0x10);
            float y = *(float*)(currentEntity + 0x9A8 + 0x14);
            float z = *(float*)(currentEntity + 0x9A8 + 0x18);

            std::cout << type << " " << x << " " << y << " " << z << std::endl;
        }

        currentEntity = *(uintptr_t*)(currentEntity + nextEntity);
    }
}