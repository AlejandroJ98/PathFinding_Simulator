#include "Precompiled.h"
#include "Entity.h"

#include "AIWorld.h"

using namespace AI;

Entity::Entity(AIWorld& world, uint32_t typeId)
	: world(world)
	, id(world.GetNextId(typeId))
{
	world.RegisterEntity(this);
}

Entity::~Entity()
{
	world.UnregisterEntity(this);
}