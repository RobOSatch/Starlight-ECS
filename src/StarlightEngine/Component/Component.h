#pragma once
#include <type_traits>

namespace Starlight
{

	struct ComponentTypeCounter
	{
		static size_t COMPONENT_TYPE_COUNTER;
	};

	template<typename T>
	struct Component
	{
	public:
		static size_t ComponentTypeId()
		{
			static size_t componentTypeId = ComponentTypeCounter::COMPONENT_TYPE_COUNTER++;
			return componentTypeId;
		}
	};

	template<typename T>
	static size_t GetComponentTypeId()
	{
		//TODO:WTF IS THIS
		return Component<typename std::remove_const<T>::type>::ComponentTypeId();
	}

	size_t ComponentTypeCounter::COMPONENT_TYPE_COUNTER = 0;
}