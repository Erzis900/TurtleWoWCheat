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
	float* getColor() { return color; }
private:
	EntityManager();

	bool IsValidEntity(uintptr_t entity) const;
	Vec3 GetEntityPos(uintptr_t entity) const;
	void DrawESPLine(const ImVec2& from, const ImVec2& to);
	void DrawESPText(const ImVec2& to, float distance);
	ImU32 GetImGuiColor(float* color);

	uintptr_t currentEntity;
	std::ptrdiff_t firstEntity;
	std::ptrdiff_t nextEntity;

	float maxDistance{ 50.f };
	bool isDistanceLimit{ false };
	float color[3] = { 0.f, 1.f, 0.f };
};