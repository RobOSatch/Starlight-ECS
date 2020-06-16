#include <../Components/TransformComponent.h>
#include <../Components/ParticleComponent.h>
#include <../Components/MouseInputComponent.h>
#include <iostream>
#include <Entity/Entity.h>
#include <omp.h>

class ParticleMoveSystem : public Starlight::System
{
	void Init()
	{
		//this->AddComponentType<MouseInputComponent>();
		this->AddComponentType<TransformComponent>();
		this->AddComponentType<RenderComponent>();
		this->AddComponentType<ParticleComponent>();
	}

	void Update(float deltaTime)
	{
		auto* particleIt = engine->GetComponentManager<ParticleComponent>()->GetIterator()->componentList;
		auto* transformIt = engine->GetComponentManager<TransformComponent>()->GetIterator()->componentList;
		auto* renderIt = engine->GetComponentManager<RenderComponent>()->GetIterator()->componentList;

		for (int i = 0; i < particleIt->size; ++i)
		{
			auto* input = singletonInput;
			auto* particle = &particleIt->data->at(i);
			auto* transform = &transformIt->data->at(i + 1);
			auto* render = &renderIt->data->at(i + 1);

			Vector2 direction = transform->m_Position - input->m_Position;

			if (direction.Length() < particle->triggerRadius)
			{
				//render->m_Color = { 0, 255, 0, 1 };
				transform->m_Position += direction.Normalize() * 20.0f;
			}
			else if (transform->m_Position.x != particle->originalPos.x
				&& transform->m_Position.y != particle->originalPos.y)
			{
				//render->m_Color = { 0, 0, 255, 1 };
				transform->m_Position = Vector2::Lerp(transform->m_Position, particle->originalPos, 0.07f);
			}

			Vector2 originDirection = transform->m_Position - particle->originalPos;
			float distance = originDirection.Length();
			float greenPercentage = distance / particle->triggerRadius;
			if (greenPercentage < 1.0f)
			{
				render->m_Color = { 0, greenPercentage * 600, 255 - 600 * greenPercentage, 1 };
			}
		}

		//for (int i = 0; i < m_registeredEntities.size(); i++)
		//{
		//	auto entity = &m_registeredEntities[i];
		//	auto* input = singletonInput;
		//	//auto* input = engine->GetComponentManager<MouseInputComponent>()->GetComponent(*entity);
		//	auto* transform = engine->GetComponentManager<TransformComponent>()->GetComponent(*entity);
		//	auto* render = engine->GetComponentManager<RenderComponent>()->GetComponent(*entity);
		//	auto* particle = engine->GetComponentManager<ParticleComponent>()->GetComponent(*entity);

		//	if (!particle) return;

		//	Vector2 direction = transform->m_Position - input->m_Position;

		//	if (direction.Length() < particle->triggerRadius)
		//	{
		//		//render->m_Color = { 0, 255, 0, 1 };
		//		transform->m_Position += direction.Normalize() * 10.0f;
		//	}
		//	else if (transform->m_Position.x != particle->originalPos.x
		//		&& transform->m_Position.y != particle->originalPos.y)
		//	{
		//		//render->m_Color = { 0, 0, 255, 1 };
		//		direction = particle->originalPos - transform->m_Position;
		//		transform->m_Position = Vector2::Lerp(transform->m_Position, particle->originalPos, 0.05f);
		//	}
		//}
	}
};