#pragma once
#include <Entity/IEntity.h>

namespace Starlight
{
	template<class T>
	class Component;

	class IComponent
	{
	private:
		ComponentID m_ComponentID;
		EntityID m_Owner;

	public:
		IComponent();
		~IComponent();

		// getters
		const ComponentID GetComponentID()
		{
			return this->m_ComponentID;
		}

		const EntityID GetOwner()
		{
			return this->m_Owner;
		}
	};
}