#pragma once
#include <Starlight.h>
#include <../Components/TransformComponent.h>
#include <../Components/CircleComponent.h>
#include <iostream>
#include <System/System.h>
#include <SDL.h>

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
			auto tranformList = engine->GetComponentManager<TransformComponent>()->GetIterator()->componentList;
			
			auto renderList = engine->GetComponentManager<RenderComponent>()->GetIterator()->componentList;

			for (size_t t= 0; t < tranformList->size; t++)
			{
				auto* transform = &tranformList->data->at(t);
				auto* render = &renderList->data->at(t);
				Vector2 pos = transform->m_Position;
				Color color = render->m_Color;

				renderer->DrawRect(pos.x, pos.y, render->m_Radius, render->m_Radius, color.r, color.g, color.b);
			}
		
			/*for (int64_t i = 0; i < m_registeredEntities.size(); ++i)
			{
				auto entity = m_registeredEntities[i];
				auto* transform = engine->GetComponentManager<TransformComponent>()->GetComponent(entity);
				auto* render = engine->GetComponentManager<RenderComponent>()->GetComponent(entity);

				Vector2 pos = transform->m_Position;
				Color color = render->m_Color;

				renderer->DrawRect(pos.x, pos.y, render->m_Radius, render->m_Radius, color.r, color.g, color.b);
			}*/

			renderer->EndFrame();
	}
};