#pragma once

#include <Starlight.h>
#include "../Vector2.h"

struct TransformComponent : public Starlight::Component<TransformComponent>
{
public:
	Vector2 m_Position;
};