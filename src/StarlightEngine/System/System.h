#pragma once
#include <bitset>
#include <vector>
#include <Entity/Entity.h>

namespace Starlight
{	
	class Engine;

	class System
	{		
	public:
		System() = default;
		virtual ~System() = default;

		virtual void Init() {};

		void RegisterEngine(Engine* engine)
		{
			this->engine = engine;
		}

		template<typename ComponentType>
		void AddComponentType()
		{
			m_registeredComponents.push_back(GetComponentTypeId<ComponentType>());
		}

		void AddEntity(Entity* entity)
		{
			this->m_registeredEntities.push_back(entity);
		}

		virtual void Update(float dt) = 0;

	protected:
		Engine* engine;
		std::vector<size_t> m_registeredComponents;
		std::vector<Entity*> m_registeredEntities;
	};
}
