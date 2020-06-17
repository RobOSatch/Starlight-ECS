#pragma once
#include <Component/ComponentTypeBitmask.h>
#include "Component/ComponentManager.h"

namespace Starlight
{	
	class Engine;
	
	class ISystem
	{
	protected:

		friend class SystemManager;
		
		virtual ~ISystem() {
			m_registeredEntities.clear();
		}
		
		virtual void ActualUpdate(float dt) = 0;
		virtual void Init() = 0;

		void RegisterEngine(Engine* engine)
		{
			this->engine = engine;
		}

		template<typename T>
		void AddComponentType()
		{
			m_bitmask.AddComponent<T>();
		}

		void AddEntity(Entity entity)
		{
			this->m_registeredEntities.push_back(entity);
		}

		void RemoveEntity(Entity entity)
		{
			for (auto it = m_registeredEntities.begin(); it != m_registeredEntities.end(); ++it)
			{
				Entity e = *it;
				if (e.id == entity.id)
				{
					m_registeredEntities.erase(it);
					return;
				}
			}
		}

		ComponentTypeBitmask GetBitmask() const
		{
			return m_bitmask;
		}

		void InvalidateCache()
		{
			m_isCacheValid = false;
		}


		bool m_isCacheValid = false;
		size_t m_cacheSize = 0;

		Engine* engine;

		
		std::vector<Entity> m_registeredEntities;
		ComponentTypeBitmask m_bitmask;

	};
}
