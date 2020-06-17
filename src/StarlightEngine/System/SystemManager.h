#pragma once
#include <System/System.h>
#include <Starlight.h>
#include <vector>
#include <Component/ComponentTypeBitmask.h>
#include <cassert>

namespace Starlight
{

	// Represents the system manage, which holds the ECSs system and is responsible for
	// initializing and updating them correctly
	class SystemManager
	{
	public:
		void AddSystem(ISystem* system, Engine* engine)
		{			
#ifdef _DEBUG
			auto itr = std::find(m_systems.begin(), m_systems.end(), system);
			assert(itr == m_systems.cend());
#endif
			m_systems.push_back(system);
			system->RegisterEngine(engine);
			system->Init();
		}

		void RemoveSystem(ISystem * system)
		{
#ifdef _DEBUG
			auto itr = std::find(m_systems.begin(), m_systems.end(), system);
			assert(itr != m_systems.cend());
#endif

			m_systems.erase(itr);		
		}

		void Init()
		{
			for (ISystem* s : m_systems) {
				s->Init();
			}
		}

		// Main loop update function
		void Update(float deltaTime)
		{
			for (ISystem* s : m_systems)
			{
				s->ActualUpdate(deltaTime);
			}
		}

		// Adds or removes entities from systems, where the updated bitmask doesn't
		// match anymore. This happens when the user adds or removes a component, so that
		// the entities bitmask and the systems bitmask match / unmatch.
		void UpdateBitmask(Entity const& entity, ComponentTypeBitmask oldBitmask)
		{
			ComponentTypeBitmask bitmask = m_bitmaskMap[entity];

			for (auto& s : m_systems)
			{
				ComponentTypeBitmask systemBitmask = s->GetBitmask();

				if (bitmask.IsNowMatched(oldBitmask, systemBitmask)) s->AddEntity(entity);
				else if (bitmask.IsNowUnmatched(oldBitmask, systemBitmask)) s->RemoveEntity(entity);
			}
		}

		// Registers the specified component type to the entity and updates the
		// systems entities accordingly
		template<typename T>
		void AddComponentType(Entity const& entity)
		{
			ComponentTypeBitmask bitmask = m_bitmaskMap[entity];
			m_bitmaskMap[entity].AddComponent<T>();

			UpdateBitmask(entity, bitmask);
		}

		// Removes the specified component type from the entity and updates the
		// systems entities accordingly
		template<typename T>
		void RemoveComponentType(Entity* const& entity)
		{
			ComponentTypeBitmask oldMask = m_bitmaskMap[entity];
			m_bitmaskMap[entity].RemoveComponent<T>();
			UpdateBitmask(entity, oldMask);
		}

		// Inalidates the caches for all the systems
		void InvalidateCaches()
		{
			for (auto* s : m_systems)
			{
				s->InvalidateCache();
			}
		}

	protected:
		std::map<Entity, ComponentTypeBitmask> m_bitmaskMap;
		std::vector<ISystem*> m_systems;
	};
}
