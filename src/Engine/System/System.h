#pragma once
#include "Component/Component.h"

class System
{
public:
	virtual void Update(float timeStep) = 0;
	virtual void NotifyComponent(Component* component) = 0;
};

