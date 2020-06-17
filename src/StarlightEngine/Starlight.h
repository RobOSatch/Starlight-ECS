#pragma once

#include <memory>
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
	public:
		Engine()
		{ 
			m_entityManager = std::make_unique<Starlight::EntityManager>();
			m_systemManager = std::make_unique<Starlight::SystemManager>();
		}
		~Engine()
		{
			m_systemManager.reset();
		}
		
		void Update(float dt) { m_systemManager.get()->Update(dt); }

		Entity CreateEntity() { return m_entityManager.get()->CreateEntity(); };
		
		void DestroyEntity(Entity entity) {
			m_systemManager->InvalidateCaches();
			//m_entityManager->destroy(entity);
		}

		void AddSystem(ISystem* system) {
			m_systemManager.get()->AddSystem(system, this);

		}

		void RemoveSystem(ISystem* system)
		{
			m_systemManager.get()->RemoveSystem(system);
		}


		template <typename ComponentType>
		void AddComponent(Entity const& entity, ComponentType&& component) {
			ComponentManager<ComponentType>* manager = GetComponentManager<ComponentType>();
			manager->AddComponent(entity, component);

			m_systemManager->AddComponentType<ComponentType>(entity);
		}

		template <typename ComponentType>
		void RemoveComponent(Entity const& entity) {
			ComponentManager<ComponentType>* manager = GetComponentManager<ComponentType>();
			ComponentType* component = manager->GetComponent(entity);
			m_systemManager->RemoveComponentType<ComponentType>(entity);
			manager->RemoveComponent(entity);

			m_systemManager->InvalidateCaches();
		}

		template <typename ComponentType>
		void CreateComponentManager() {
			int componentTypeId = GetComponentTypeId<ComponentType>();

			if (componentTypeId >= m_componentManagers.size()) {
				m_componentManagers.resize(componentTypeId + 1);
			}
			if (!m_componentManagers[componentTypeId]) {
				m_componentManagers[componentTypeId] = std::make_unique<ComponentManager<ComponentType>>(this);
			}
		}

		template <typename ComponentType>
		ComponentManager<ComponentType>* GetComponentManager() const {
			int componentTypeId = GetComponentTypeId<ComponentType>();
			return static_cast<ComponentManager<ComponentType>*>(m_componentManagers[componentTypeId].get());
		}
	private:
		std::unique_ptr<EntityManager> m_entityManager;
		std::unique_ptr<SystemManager> m_systemManager;

		std::vector<std::unique_ptr<IComponentManager>> m_componentManagers;
	};
}