#pragma once
#include <Component/ComponentTypeBitmask.h>
#include "Component/ComponentManager.h"

namespace Starlight
{	
	class Engine;
	
	// Interface class for a system
	class ISystem
	{
	protected:

		friend class SystemManager;
		
		virtual ~ISystem() {
			m_registeredEntities.clear();
		}

		// Initializer function, which has to be overriden. This is the place, where
		// the API user can specify the systems component types
		virtual void Init() = 0;
		
		// Update function, which is overriden in the System class
		virtual void ActualUpdate(float dt) = 0;
		
		// Sets the systems engine reference
		void RegisterEngine(Engine* engine)
		{
			this->engine = engine;
		}

		// Adds the specified component type to the systems bitmask
		template<typename T>
		void AddComponentType()
		{
			m_bitmask.AddComponent<T>();
		}

		// Adds the specified entity to the systems entities
		void AddEntity(Entity entity)
		{
			this->m_registeredEntities.push_back(entity);
		}

		// Removes an entity from the system
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

		// Invalidates the systems cache, indicating that it needs
		// to fetch new data
		void InvalidateCache()
		{
			m_isCacheValid = false;
		}

		ComponentTypeBitmask GetBitmask() const
		{
			return m_bitmask;
		}

		bool m_isCacheValid = false;
		size_t m_cacheSize = 0;

		Engine* engine;

		std::vector<Entity> m_registeredEntities;
		ComponentTypeBitmask m_bitmask;

	};
}
