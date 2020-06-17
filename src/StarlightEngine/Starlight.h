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
	// Main engine class
	// Handles user access to the Entity Component System
	// containes all managers
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
		
		// Main update function. Updates systemManager, which internally updates all systems.
		void Update(float dt) { m_systemManager.get()->Update(dt); }

		Entity CreateEntity() { return m_entityManager.get()->CreateEntity(); };

		// Removes the entity entirely from the "engine"
		void DestroyEntity(Entity entity) {


 			for (auto i = std::next(m_componentManagers.begin()); i != m_componentManagers.end(); ++i)
			{
				auto manager = i->get();
				manager->RemoveComponent(entity);
			}
			
			m_systemManager->InvalidateCaches();

		}

		// Register a new system to the ECS
		// System gets initialized with this call
		void AddSystem(ISystem* system) {
			m_systemManager.get()->AddSystem(system, this);
		}

		// Removes the specified system from the ECS
		void RemoveSystem(ISystem* system)
		{
			m_systemManager.get()->RemoveSystem(system);
		}

		// Adds a component. The component type has to be specified.
		// The type gets referenced to the systems, so the systems can use it to cache relevant entities.
		// After the add, the systems have to update their caches to check if an entity now falls into
		// their scope
		template <typename ComponentType>
		void AddComponent(Entity const& entity, ComponentType&& component) {
			ComponentManager<ComponentType>* manager = GetComponentManager<ComponentType>();
			manager->AddComponent(entity, component);
			m_systemManager->AddComponentType<ComponentType>(entity);
			
			m_systemManager->InvalidateCaches();
		}

		// Removes a component. 
		// Caches get updated after a delte
		template <typename ComponentType>
		void RemoveComponent(Entity const& entity) {
			ComponentManager<ComponentType>* manager = GetComponentManager<ComponentType>();
			manager->RemoveComponent(entity);
			m_systemManager->RemoveComponentType<ComponentType>(entity);

			m_systemManager->InvalidateCaches();
		}

		//Creates a component manager for the specified component type
		//Allocates memory for 0x000FFFFF (~1 000 000) components
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