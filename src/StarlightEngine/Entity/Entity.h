#pragma once
#include <Entity/IEntity.h>

namespace Starlight
{
	template<class T>
	class Entity : public IEntity
	{

	public:
		Entity() {}
		virtual ~Entity() {}

	};
}

