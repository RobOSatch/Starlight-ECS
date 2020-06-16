#pragma once
#include <bitset>
#include <vector>
#include <Entity/Entity.h>
#include <System/ISystem.h>
#include <Component/ComponentTypeBitmask.h>

namespace Starlight
{	
	class Engine;

	template<typename TupleType>
	class System : public ISystem
	{
	public:
		System() = default;
		virtual ~System() = default;

		virtual void Init() {};

		void ActualUpdate(float dt)
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

		virtual void Update(std::array<TupleType, 0x000FFFFF>* tuples, float dt) = 0;

		virtual TupleType MakeTuple(Entity e) = 0;

	protected:
		
		
		std::array<TupleType, 0x000FFFFF> m_tuples;
	};
}
