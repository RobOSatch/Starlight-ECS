#pragma once
#include "Component.h"

struct Color
{
	float r, g, b, a;
};

class Circle : Component
{
	float radius;
	Color color;
};