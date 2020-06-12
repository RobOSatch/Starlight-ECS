#include "EntityAdmin.h"

void EntityAdmin::Update(float timeStep)
{
	for (System* s : m_systems)
	{
		s->Update(timeStep);
	}
}
