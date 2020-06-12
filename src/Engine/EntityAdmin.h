#pragma once
#include "System/System.h"
#include "Entity/Entity.h"
#include "Component/Component.h"
#include <unordered_map>
#include <vector>

class EntityAdmin
{
public:
	void Update(float timeStep);
private:
	std::vector<System*> m_systems;
	std::unordered_map<int, Entity*> m_entities;
	std::vector<Component*> m_components;

};

