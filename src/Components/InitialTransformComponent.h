#pragma once

#include <Starlight.h>

#include "../Vector2.h"

struct InitialTransformComponent : Starlight::Component<InitialTransformComponent>
{
public:
	Vector2 m_Position;
};

