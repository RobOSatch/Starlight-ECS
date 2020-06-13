#pragma once

#include <Utils/TypeWrapper.h>
#include <Component/ComponentManager.h>

namespace Starlight
{
	class IEntity
	{
	public:
		IEntity();
		~IEntity();
	private:
		// set on create; in EntityManager
		ComponentManager*	m_ComponentManagerInstance;
	protected:
		EntityID m_EntityID;
	};
}