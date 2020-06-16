#pragma once
#include <Starlight.h>
#include <../Components/TransformComponent.h>
#include <../Components/CircleComponent.h>
#include <iostream>
#include <System/System.h>
#include <SDL.h>
#include <omp.h>


class RenderSystem : public Starlight::System
{
	Renderer* renderer;

public:
	RenderSystem(Renderer* renderer)
	{
		this->renderer = renderer;
	}

	void Init()
	{
		this->AddComponentType<TransformComponent>();
		this->AddComponentType<RenderComponent>();
	}

	void Update(float deltaTime)
	{
		renderer->BeginFrame();

		auto* transformIt = engine->GetComponentManager<TransformComponent>()->GetIterator()->componentList;
		auto* renderIt = engine->GetComponentManager<RenderComponent>()->GetIterator()->componentList;

		for (int i = 0; i < transformIt->size; ++i)
		{
			auto* transform = &transformIt->data->at(i);
			auto* render = &renderIt->data->at(i);

			Vector2 pos = transform->m_Position;
			Color color = render->m_Color;

			renderer->DrawRect(pos.x, pos.y, render->m_Radius, render->m_Radius, color.r, color.g, color.b);
		}

		/*for (auto entity : m_registeredEntities)
		{
			auto* transform = engine->GetComponentManager<TransformComponent>()->GetComponent(entity);
			auto* render = engine->GetComponentManager<RenderComponent>()->GetComponent(entity);

			Vector2 pos = transform->m_Position;
			Color color = render->m_Color;
			
			renderer->DrawRect(pos.x, pos.y, render->m_Radius, render->m_Radius, color.r, color.g, color.b);
		}*/

		renderer->EndFrame();
	}
};