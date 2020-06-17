#pragma once
#include <type_traits>
#include <cstdint>

namespace Starlight
{

	using ComponentID = uint32_t;
	// A counter, starting with 0, giving each type of component an unique id
	struct ComponentTypeCounter
	{
		static size_t COMPONENT_TYPE_COUNTER;
	};

	// Base struct for a component. This is going to serve as the generic super class
	// for each specific component
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

	// Returns the components type id
	template<typename T>
	static size_t GetComponentTypeId()
	{
		return Component<typename std::remove_const<T>::type>::ComponentTypeId();
	}
}
