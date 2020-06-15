#pragma once

#include <Starlight.h>
#include "../Vector2.h"

struct ParticleComponent : public Starlight::Component<ParticleComponent>
{
public:
	Vector2 originalPos;
	float triggerRadius;
};