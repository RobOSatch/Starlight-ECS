#include <../Components/TransformComponent.h>
#include <../Components/ParticleComponent.h>
#include <../Components/MouseInputComponent.h>
#include <iostream>
#include <Entity/Entity.h>
#include <omp.h>

struct ParticleTuple
{
	ParticleComponent* particle;
	TransformComponent* transform;
	RenderComponent* render;
};


//particles get "pushed away" based on the input
class ParticleMoveSystem : public Starlight::System<ParticleTuple>
{

	void Init() override
	{
		this->AddComponentType<TransformComponent>();
		this->AddComponentType<RenderComponent>();
		this->AddComponentType<ParticleComponent>();
	}

	ParticleTuple MakeTuple(Starlight::Entity e) override
	{
		auto* transform = engine->GetComponentManager<TransformComponent>()->GetComponent(e);
		auto* render = engine->GetComponentManager<RenderComponent>()->GetComponent(e);
		auto* particle = engine->GetComponentManager<ParticleComponent>()->GetComponent(e);

		return { particle, transform, render };
	}

	void Update(std::array<ParticleTuple, 0x000FFFFF>* tuples, float dt) override
	{
		auto* input = singletonInput;

		for (auto it = tuples->begin(); it != tuples->begin() + m_cacheSize; ++it)
		{
			auto* transform = it->transform;
			auto* render = it->render;
			auto* particle = it->particle;

			//push
			Vector2 direction = transform->m_Position - input->m_Position;

			if (direction.Length() < particle->triggerRadius)
			{
				//render->m_Color = { 0, 255, 0, 1 };
				transform->m_Position += direction.Normalize() * 10.0f;
			}
			else if (transform->m_Position.x != particle->originalPos.x
				&& transform->m_Position.y != particle->originalPos.y)
			{
				//render->m_Color = { 0, 0, 255, 1 };
				direction = particle->originalPos - transform->m_Position;
				transform->m_Position = Vector2::Lerp(transform->m_Position, particle->originalPos, 0.05f);
			}

			Vector2 originDirection = transform->m_Position - particle->originalPos;
			float distance = originDirection.Length();
			float greenPercentage = distance / particle->triggerRadius;
			if (greenPercentage < 1.0f)
			{
				render->m_Color = { greenPercentage * 255, 0, 255, 1 };
			}
		}
	}
};