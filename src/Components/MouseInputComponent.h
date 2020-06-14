#pragma once
#include <Starlight.h>
#include "../Vector2.h"

struct MouseInputComponent : Starlight::Component<MouseInputComponent>
{
public:
	Vector2 m_Position;
};

