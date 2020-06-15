#pragma once
#include <Starlight.h>
#include <../Components/MouseInputComponent.h>
#include <iostream>
#include <System/System.h>
#include <SDL.h>


class InputSystem : public Starlight::System
{
	void Init()
	{
		this->AddComponentType<MouseInputComponent>();
	}

	void Update(float deltaTime)
	{
		for (auto entity : m_registeredEntities)
		{
			auto* input = engine->GetComponentManager<MouseInputComponent>()->GetComponent(entity);
			int x, y;
			SDL_GetMouseState(&x, &y);
			Vector2 pos;
			pos.x = x;
			pos.y = y;

			input->m_Position = pos;
		}

	}
};