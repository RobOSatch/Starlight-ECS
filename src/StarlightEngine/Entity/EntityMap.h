#pragma once
#include <Entity/Entity.h>

#include <array>
#include <map>

namespace Starlight
{
	const size_t MAX_COMPONENTS = 0x000FFFFF;
	using ComponentId = size_t;

	struct EntityMap
	{
		std::map<Entity, ComponentId> m_ComponentMap;
		std::array<Entity, MAX_COMPONENTS> m_EntityMap;

		Entity GetEntity(ComponentId c) { return m_EntityMap.at(c); }
		ComponentId GetComponent(Entity e) { return m_ComponentMap.at(e); }

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