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
		Engine(std::unique_ptr<EntityManager> entityManager) : m_entityManager(std::move(entityManager))
		{
			m_systemManager = std::make_unique<Starlight::SystemManager>();
		}
		~Engine()
		{
			m_systemManager.reset();
		}


		void Init()
		{
			m_systemManager.get()->Init();
		};

		void Update(float dt) { m_systemManager.get()->Update(dt); }

		Entity CreateEntity() { return m_entityManager.get()->CreateEntity(); };
		void AddSystem(ISystem* system) {
			system->RegisterEngine(this);
			m_systemManager.get()->AddSystem(system);
		}


		//		void DestroyEntity(Entity entity) {
		//			for (auto& system : systems) {
		//				system->unRegisterEntity(entity);
		//			}
		//
		//			m_entityManager->destroy(entity);
		//		}



		template <typename ComponentType>
		void AddCustomComponentManager(std::unique_ptr<ComponentManager<ComponentType>> manager) {
			int componentTypeId = GetComponentTypeId<ComponentType>();
			if (componentTypeId >= m_componentManagers.size()) {
				m_componentManagers.resize(componentTypeId + 1);
			}
			m_componentManagers[componentTypeId] = manager;
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
		
		std::unique_ptr<EntityManager> m_entityManager;
		std::unique_ptr<SystemManager> m_systemManager;
		std::vector<std::unique_ptr<IComponentManager>> m_componentManagers;

		template <typename T>
		ComponentManager<T>* GetComponentManager() {
			// Need to make sure we actually have a component manager.
			// TODO(taurheim) this is a performance hit every time we add and remove a component
			int componentTypeId = GetComponentTypeId<T>();

			if (componentTypeId >= m_componentManagers.size()) {
				m_componentManagers.resize(componentTypeId + 1);
			}

			if (!m_componentManagers[componentTypeId]) {
				m_componentManagers[componentTypeId] = std::make_unique<ComponentManager<T>>(this);
			}

			return static_cast<ComponentManager<T>*>(m_componentManagers[componentTypeId].get());
		}

	private:
	};
}