#pragma once

#include "Entity.h"

namespace AI
{
	class AIWorld
	{
	public:
		void RegisterEntity(Entity* entity);
		void UnregisterEntity(Entity* entity);

		uint64_t GetNextId(uint32_t typeId);

	private:
		Entities mEntities;
		uint64_t mNextId = 0;
	};
}