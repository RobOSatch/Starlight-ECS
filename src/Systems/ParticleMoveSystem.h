#include <../Components/TransformComponent.h>
#include <../Components/ParticleComponent.h>
#include <../Components/MouseInputComponent.h>
#include <iostream>
#include <Entity/Entity.h>

class ParticleMoveSystem : public Starlight::System
{
	void Update(float deltaTime)
	{


		auto tranformList = engine->GetComponentManager<TransformComponent>()->GetIterator()->componentList;
		auto* inputList = engine->GetComponentManager<MouseInputComponent>()->GetIterator()->componentList;
		auto particleList = engine->GetComponentManager<ParticleComponent>()->GetIterator()->componentList;

		auto* input = &inputList->data->at(0);
		for (size_t t = 0; t < particleList->size; t++)
		{
			auto* transform = &tranformList->data->at(t+1);
			auto* particle = &particleList->data->at(t);
			
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
		}

		
		/*
		for (int64_t i = 0; i < m_registeredEntities.size(); ++i)
		{
			auto entity = m_registeredEntities[i];
			auto* input = engine->GetComponentManager<MouseInputComponent>()->GetComponent(entity);
			auto* transform = engine->GetComponentManager<TransformComponent>()->GetComponent(entity);
			//auto* render = engine->GetComponentManager<RenderComponent>()->GetComponent(entity);
			auto* particle = engine->GetComponentManager<ParticleComponent>()->GetComponent(entity);

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
		}
		*/
	}
};