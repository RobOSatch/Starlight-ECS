#pragma once

#include "Entity/Entity.h"
#include "Component/Component.h"
#include "System/System.h"

#include "Entity/EntityManager.h"
#include "Component/ComponentManager.h"
#include "System/SystemManager.h"

namespace Starlight
{

	class Engine
	{
		EntityManager* m_entityManager;
		ComponentManager* m_componentManager;
		SystemManager* m_systemManager;

	public:
		Engine();
		~Engine();

		void Update(float deltaTime);

		EntityManager* GetEntityManager()
		{
			return this->m_entityManager;
		}

		ComponentManager* GetComponentManager()
		{
			return this->m_componentManager;
		}

		SystemManager* GetSystemManager()
		{
			return this->m_systemManager;
		}
	};
}