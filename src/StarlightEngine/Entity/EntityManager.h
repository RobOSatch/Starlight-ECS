#pragma once
#include <Entity/Entity.h>

namespace Starlight
{
	// This class represents the entity manager and is responsible for giving out the next
	// available EntityId to the API user.
	class EntityManager
	{
	public:
		Entity CreateEntity()
		{
			Entity entity;
			entity.id = m_nextId++;
			return entity;
		}
	
	private:
		size_t m_nextId = 0;
	};
}