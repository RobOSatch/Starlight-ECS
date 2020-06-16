#pragma once
#include <System/System.h>
#include <vector>

namespace Starlight
{
	class SystemManager
	{
	public:
		void AddSystem(System* system)
		{
			m_systems.push_back(system);
		}

		void Update(float deltaTime)
		{
			for (System* s : m_systems)
			{
				s->Update(deltaTime);
			}
		}

		void Init()
		{
			for (System* system : m_systems) {
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
				//else if (bitmask.IsNowUnmatched(oldBitmask, systemBitmask)) system->RemoveEntity(entity);
			}
		}

		template<typename T>
		void AddComponentType(Entity const& entity)
		{
			ComponentTypeBitmask bitmask = m_bitmaskMap[entity];
			m_bitmaskMap[entity].AddComponent<T>();

			UpdateBitmask(entity, bitmask);
		}

	protected:
		std::map<Entity, ComponentTypeBitmask> m_bitmaskMap;
		std::vector<System*> m_systems;
	};
}