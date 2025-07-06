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
    currentEntity = *(DWORD*)(*Base::Addr::entityManager + Base::Offset::firstEntity);
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

            AddEntity(x, y, z);
            std::cout << type << " " << x << " " << y << " " << z << std::endl;
        }

        currentEntity = *(DWORD*)(currentEntity + Base::Offset::nextEntity);
    }
}

void EntityManager::AddEntity(float x, float y, float z)
{
    Entity ent;
    ent.x = x;
    ent.y = y;
    ent.z = z;

    entities.push_back(ent);
}