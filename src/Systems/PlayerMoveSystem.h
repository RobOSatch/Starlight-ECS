#pragma once
#include <Starlight.h>
#include <../Components/TransformComponent.h>
#include <../Components/MouseInputComponent.h>
#include <iostream>
#include <Entity/Entity.h>

class PlayerMoveSystem : public Starlight::System
{
	void Update(float deltaTime)
	{
		for (auto entity : m_registeredEntities)
		{
			auto* input = engine->GetComponentManager<MouseInputComponent>()->GetComponent(*entity);
			auto* transform = engine->GetComponentManager<TransformComponent>()->GetComponent(*entity);

			transform->m_Position = input->m_Position;
		}
	}
};