#include "Precompiled.h"
#include "AIWorld.h"

using namespace AI;

void AIWorld::RegisterEntity(Entity* entity)
{
	mEntities.push_back(entity);
}

void AIWorld::UnregisterEntity(Entity* entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);
	if (iter != mEntities.end())
	{
		std::iter_swap(iter, mEntities.end() - 1);
		mEntities.pop_back();
	}
}

uint64_t AIWorld::GetNextId(uint32_t typeId)
{
	uint64_t id = typeId;
	id <<= 32;
	id |= mNextId++;
	return id;
}
