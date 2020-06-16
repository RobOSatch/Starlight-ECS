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

class ParticleMoveSystem : public Starlight::System<ParticleTuple>
{
	size_t cacheSize = 0;
	std::array<ParticleTuple, 0x000FFFFF> m_particleTuples;

	void Init()
	{
		//this->AddComponentType<MouseInputComponent>();
		this->AddComponentType<TransformComponent>();
		this->AddComponentType<RenderComponent>();
		this->AddComponentType<ParticleComponent>();
	}

	ParticleTuple MakeTuple(Starlight::Entity e)
	{
		auto* transform = engine->GetComponentManager<TransformComponent>()->GetComponent(e);
		auto* render = engine->GetComponentManager<RenderComponent>()->GetComponent(e);
		auto* particle = engine->GetComponentManager<ParticleComponent>()->GetComponent(e);

		return { particle, transform, render };
	}

	void Update(std::array<ParticleTuple, 0x000FFFFF>* tuples, float dt)
	{
		auto* input = singletonInput;

		for (auto it = tuples->begin(); it != tuples->begin() + m_cacheSize; ++it)
		{
			auto* transform = it->transform;
			auto* render = it->render;
			auto* particle = it->particle;

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
				render->m_Color = { 0, greenPercentage * 600, 255 - 600 * greenPercentage, 1 };
			}
		}
	}

	//void Update(ParticleTuple* tuple)
	//{
	//	auto* input = singletonInput;
	//	auto* transform = tuple->transform;
	//	auto* render = tuple->render;
	//	auto* particle = tuple->particle;

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

	//	Vector2 originDirection = transform->m_Position - particle->originalPos;
	//	float distance = originDirection.Length();
	//	float greenPercentage = distance / particle->triggerRadius;
	//	if (greenPercentage < 1.0f)
	//	{
	//		render->m_Color = { 0, greenPercentage * 600, 255 - 600 * greenPercentage, 1 };
	//	}
	//}

	//void Update(float deltaTime)
	//{
	//	if (m_isCacheValid)
	//	{
	//		for (auto it = m_particleTuples.begin(); it != m_particleTuples.begin() + cacheSize; ++it)
	//		{
	//			UpdateComponents(&*it);
	//		}
	//	}
	//	else
	//	{
	//		cacheSize = 0;
	//		m_isCacheValid = true;
	//		for (int i = 0; i < m_registeredEntities.size(); i++)
	//		{
	//			cacheSize++;
	//			
	//			auto entity = &m_registeredEntities[i];
	//			ParticleTuple t = MakeTuple(entity);

	//			auto* transform = engine->GetComponentManager<TransformComponent>()->GetComponent(*entity);
	//			auto* render = engine->GetComponentManager<RenderComponent>()->GetComponent(*entity);
	//			auto* particle = engine->GetComponentManager<ParticleComponent>()->GetComponent(*entity);

	//			m_particleTuples.at(i) = { particle, transform, render };

	//			UpdateComponents(&m_particleTuples.at(i));
	//		}
	//	}	
	//}
};