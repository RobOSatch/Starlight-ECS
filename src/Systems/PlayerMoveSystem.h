#pragma once
#include <Starlight.h>
#include <../Components/TransformComponent.h>
#include <../Components/MouseInputComponent.h>
#include <iostream>
#include <Entity/Entity.h>

struct PlayerTuple
{
	TransformComponent* transform;
	TagComponent* tag;
};

class PlayerMoveSystem : public Starlight::System<PlayerTuple>
{
	void Init()
	{
		this->AddComponentType<TransformComponent>();
		this->AddComponentType<TagComponent>();
	}

	PlayerTuple MakeTuple(Starlight::Entity e)
	{
		auto* transform = engine->GetComponentManager<TransformComponent>()->GetComponent(e);
		auto* tag = engine->GetComponentManager<TagComponent>()->GetComponent(e);

		return { transform, tag};
	}

	
	void Update(std::array<PlayerTuple, 0x000FFFFF>* tuples, float dt)
	{
		auto* input = singletonInput;
		for (auto it = tuples->begin(); it != tuples->begin() + m_cacheSize; ++it)
		{
			auto* transform = it->transform;
			transform->m_Position = input->m_Position;
		}
	}
};