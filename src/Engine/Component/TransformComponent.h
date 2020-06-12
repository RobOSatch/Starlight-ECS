#pragma once
#include "Component.h"
#include "../Utils/Vector2.h"

class Transform : Component
{
private:
	Vector2 position;
	Vector2 rotation;
	Vector2 scale;
};