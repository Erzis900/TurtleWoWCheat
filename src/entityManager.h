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
	
private:
	EntityManager();

	uintptr_t currentEntity;
	std::ptrdiff_t firstEntity;
	std::ptrdiff_t nextEntity;
};