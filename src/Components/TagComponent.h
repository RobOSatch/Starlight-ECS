#pragma once

#include <Starlight.h>
#include "../Vector2.h"

struct TagComponent : public Starlight::Component<TagComponent>
{
public:
	size_t tag;
};