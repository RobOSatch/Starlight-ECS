#pragma once
#include <Entity/Entity.h>

#include <array>
#include <map>

namespace Starlight
{
	const size_t MAX_COMPONENTS = 0x000FFFFF;
	using ComponentId = size_t;

	// A doubly linked map that maps entities to components and vice versa. One
	// entity map is used for exactly one type of component.
	struct EntityMap
	{
		std::map<Entity, ComponentId> m_ComponentMap;
		std::array<Entity, MAX_COMPONENTS> m_EntityMap;

		Entity GetEntity(ComponentId c) const { return m_EntityMap.at(c); }
		const ComponentId* GetComponent(Entity e) const
		{

			if (m_ComponentMap.count(e))
			{
				return &m_ComponentMap.at(e);
			}
			return nullptr;

		}

		// Basic map operations
		void Add(Entity e, ComponentId c)
		{
			m_ComponentMap.insert({ e,c });
			m_EntityMap[c] = e;
		}

		void Update(Entity e, ComponentId c)
		{
			m_ComponentMap.at(e) = c;
			m_EntityMap[c] = e;
		}

		void Delete(Entity e)
		{
			m_ComponentMap.erase(e);
		}
	};
}