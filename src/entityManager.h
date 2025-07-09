#pragma once
#include "base.h"

enum EntityType : int
{
	UNIT = 3,
	PLAYER = 4,
};

class EntityManager
{
public:
	static EntityManager& Get();
	void Update();
	
	float& GetMaxDistance() { return maxDistance; }
	bool& GetIsDistanceLimit() { return isDistanceLimit; }
	void SetMaxDistance(float distance) { maxDistance = distance; }
private:
	EntityManager();

	bool IsValidEntity(uintptr_t entity) const;
	Vec3 GetEntityPos(uintptr_t entity) const;
	void DrawLine(const Vec3& from, const Vec3& to);

	uintptr_t currentEntity;
	std::ptrdiff_t firstEntity;
	std::ptrdiff_t nextEntity;

	float maxDistance{ 50.f };
	bool isDistanceLimit{ false };
};