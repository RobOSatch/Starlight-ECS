#pragma once
#include <System/System.h>
#include <Starlight.h>
#include <vector>
#include <Component/ComponentTypeBitmask.h>
#include <cassert>

namespace Starlight
{
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

		void Update(float deltaTime)
		{
			for (ISystem* s : m_systems)
			{
				s->ActualUpdate(deltaTime);
			}
		}

		void Init()
		{
			for (ISystem* s : m_systems) {
				s->Init();
			}
		}

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

		template<typename T>
		void AddComponentType(Entity const& entity)
		{
			ComponentTypeBitmask bitmask = m_bitmaskMap[entity];
			m_bitmaskMap[entity].AddComponent<T>();

			UpdateBitmask(entity, bitmask);
		}

		template<typename T>
		void RemoveComponentType(Entity* const& entity)
		{
			ComponentTypeBitmask oldMask = m_bitmaskMap[entity];
			m_bitmaskMap[entity].RemoveComponent<T>();
			UpdateBitmask(entity, oldMask);
		}

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
