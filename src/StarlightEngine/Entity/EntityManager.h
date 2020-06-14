#pragma once
#include <Entity/Entity.h>

namespace Starlight
{
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