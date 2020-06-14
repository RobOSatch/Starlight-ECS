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

		void init()
		{
			for (System* system : m_systems) {
				system->Init();
			}
		}

	private:
		std::vector<System*> m_systems;
	};
}