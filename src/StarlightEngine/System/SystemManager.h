#pragma once
#include <System/System.h>
#include <Starlight.h>
#include <vector>
#include <Component/ComponentTypeBitmask.h>

namespace Starlight
{
	class SystemManager
	{
	public:
		void AddSystem(ISystem* system)
		{
			m_systems.push_back(system);
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
			for (ISystem* system : m_systems) {
				system->Init();
			}
		}

		void UpdateBitmask(Entity const& entity, ComponentTypeBitmask oldBitmask)
		{
			ComponentTypeBitmask bitmask = m_bitmaskMap[entity];

			for (auto& system : m_systems)
			{
				ComponentTypeBitmask systemBitmask = system->GetBitmask();

				if (bitmask.IsNowMatched(oldBitmask, systemBitmask)) system->AddEntity(entity);
				else if (bitmask.IsNowUnmatched(oldBitmask, systemBitmask)) system->RemoveEntity(entity);
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
		void RemoveComponentType(Entity const& entity)
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