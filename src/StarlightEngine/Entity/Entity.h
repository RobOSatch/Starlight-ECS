#pragma once
#include <Utils/TypeWrapper.h>

namespace Starlight
{
	struct Entity {
		EntityID id;

		friend bool operator<(const Entity& l, const Entity& r) { return l.id < r.id; }
	};
}

