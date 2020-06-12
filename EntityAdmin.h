#pragma once
#include "System.h"
#include "Entity.h"
#include "Component.h"
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

