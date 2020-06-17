#pragma once
#include <bitset>
#include <vector>
#include <Entity/Entity.h>
#include <System/ISystem.h>
#include <Component/ComponentTypeBitmask.h>

namespace Starlight
{	

	// Generic class representing a system
	template<typename TupleType>
	class System : public ISystem
	{
	public:
		System() = default;
		virtual ~System() = default;

		virtual void Init() {};

		// This update function does caching on the systems entities to improve performance
		// drastically. It works generically on all custom systems.
		void ActualUpdate(float dt) override
		{
			if (m_isCacheValid)
			{
				Update(&m_tuples, dt);
			}
			else
			{
				m_cacheSize = 0;
				m_isCacheValid = true;
				for (int i = 0; i < m_registeredEntities.size(); i++)
				{
					m_cacheSize++;

					auto entity = &m_registeredEntities[i];
					TupleType t = MakeTuple(*entity);

					m_tuples.at(i) = t;
				}
				
				Update(&m_tuples, dt);
			}
		}

		// Update function, which the user of the API has to override. This function does
		// the data updates for the components and implements the systems logic.
		virtual void Update(std::array<TupleType, 0x000FFFFF>* tuples, float dt) = 0;

		// Tuple factory function, which the user of the API has to override. This function
		// is there to make the ActualUpdate() function possible.
		virtual TupleType MakeTuple(Entity e) = 0;

	protected:
		std::array<TupleType, 0x000FFFFF> m_tuples;
	};
}
