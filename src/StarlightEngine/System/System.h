#pragma once
#include <bitset>
#include <vector>
#include <Entity/Entity.h>
#include <Component/ComponentTypeBitmask.h>

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

		template<typename T>
		void AddComponentType()
		{
			m_bitmask.AddComponent<T>();
		}

		void AddEntity(Entity entity)
		{
			this->m_registeredEntities.push_back(entity);
		}

		virtual void Update(float dt) = 0;

		ComponentTypeBitmask GetBitmask()
		{
			return m_bitmask;
		}

	protected:
		Engine* engine;
		std::vector<size_t> m_registeredComponents;
		std::vector<Entity> m_registeredEntities;

		ComponentTypeBitmask m_bitmask;
	};
}
