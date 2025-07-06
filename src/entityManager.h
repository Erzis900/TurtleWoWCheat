#pragma once
#include <vector>
#include "base.h"

struct Entity
{
	float x;
	float y;
	float z;
};

class EntityManager
{
public:
	static EntityManager& Get();
	void Update();
	
private:
	EntityManager();

	void AddEntity(float x, float y, float z);
	std::vector<Entity> entities;
	DWORD currentEntity;
};