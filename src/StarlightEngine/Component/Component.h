#pragma once
#include "IComponent.h"

namespace Starlight
{
	template<class T>
	class Component : public IComponent
	{
	public:
		static const size_t STATIC_COMPONENT_TYPE_ID;

		Component() {}
		~Component() {}
	};

	template<class T>
	const ComponentID Component<T>::STATIC_COMPONENT_TYPE_ID = -1;
}