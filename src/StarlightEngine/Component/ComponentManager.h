#pragma once

#include <Component/IComponent.h>
#include <vector>

namespace Starlight
{
	class ComponentManager
	{		
		using EntityComponentMap = std::vector<std::vector<ComponentID>>;
		EntityComponentMap m_EntityComponentMap;
	};
}