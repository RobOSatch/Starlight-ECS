#pragma once
#include <Starlight.h>
#include <../Components/TransformComponent.h>
#include <../Components/CircleComponent.h>
#include <iostream>
#include <System/System.h>
#include <SDL.h>
#include <omp.h>

struct RenderTuple
{
	TransformComponent* transform;
	RenderComponent* render;
};

class RenderSystem : public Starlight::System<RenderTuple>
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

	RenderTuple MakeTuple(Starlight::Entity e)
	{
		auto* transform = engine->GetComponentManager<TransformComponent>()->GetComponent(e);
		auto* render = engine->GetComponentManager<RenderComponent>()->GetComponent(e);

		return { transform, render };
	}

	void Update(std::array<RenderTuple, 0x000FFFFF>* tuples, float dt)
	{
		renderer->BeginFrame();

		for (auto it = tuples->begin(); it != tuples->begin() + m_cacheSize; ++it)
		{
			auto* transform = it->transform;
			auto* render = it->render;

			Vector2 pos = transform->m_Position;
			Color color = render->m_Color;

			renderer->DrawRect(pos.x, pos.y, render->m_Radius, render->m_Radius, color.r, color.g, color.b);
		}

		renderer->EndFrame();

	}
};