#pragma once
#include "Component.h"
#include "../Utils/Vector2.h"

class Particle : Component
{
	float velocity;
	Vector2 direction;
};