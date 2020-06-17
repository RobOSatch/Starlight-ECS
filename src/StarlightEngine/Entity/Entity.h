#pragma once
#include <Component/Component.h>

namespace Starlight
{


	using EntityID = uint32_t;
	// A simple representation of an entity. This struct, for now, only holds the entities
	// id.
	struct Entity {
		EntityID id;
		friend bool operator<(const Entity& l, const Entity& r) { return l.id < r.id;}
	};
}

