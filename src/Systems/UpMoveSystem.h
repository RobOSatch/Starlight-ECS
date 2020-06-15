#pragma once
#include <Starlight.h>
#include <../Components/TransformComponent.h>
#include <iostream>
#include <Entity/Entity.h>

class UpMoveSystem : public Starlight::System
{
	void Update(float deltaTime)
	{
		/*
		auto transformComponents = engine->GetComponentManager<TransformComponent>()->GetIterator();

		for (auto it = transformComponents->begin(); it != transformComponents->end(); it++)
		{
			it->m_Position.y += 1;
			std::cout << it->m_Position.x << std::endl;
		}
		*/
		/*for(Entity* e : m_registeredEntities)
		{
			TransformComponent* t = engine->GetComponentManager<TransformComponent>()->GetComponent(*e);			
			t->m_Position.y += 1;
			std::cout << t->m_Position.x << std::endl;
			
		}*/
	}
};