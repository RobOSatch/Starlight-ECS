#pragma once

#include <Component/Component.h>
#include <Entity/Entity.h>
#include <Entity/EntityMap.h>

#include <array>
#include <map>

namespace Starlight
{
	class Engine;
	
	// Memory allocation for the component type. The componets are going to be
	// placed contiguously in memory
	template<typename T>
	struct ComponentList
	{
		size_t size = 0;
		std::array<T, MAX_COMPONENTS>* data;
	};

	// Interface for the component managers. This is needed to make things work
	// with generic programming
	class IComponentManager
	{
	public:
		IComponentManager() = default;
		virtual ~IComponentManager() = default;
		virtual void RemoveComponent(Entity entity) = 0;

	};

	// Generic class representing the component manager for a single component type.
	// Each type of component will have its own manager
	template<typename T>
	class ComponentManager : public IComponentManager
	{		
	private:
		ComponentList<T> m_componentList;
		EntityMap m_entityMap;
		Engine* m_engine;

	public:
		ComponentManager(Engine* engine)
		{
			this->m_engine = engine;
			m_componentList.data = static_cast<std::array<T, MAX_COMPONENTS>*>(malloc(sizeof(T) * MAX_COMPONENTS));
		}
		
		~ComponentManager()
		{
			delete[](m_componentList.data);
		}

		// Adds the specified component to the manager and links it to the
		// specified entity
		ComponentId AddComponent(Entity entity, T& component)
		{
			ComponentId id = m_componentList.size;
			m_componentList.data->at(id) = component;
			m_componentList.size++;
			m_entityMap.Add(entity, id);

			return id;
		}

		// Removes the component for the managers type from the specified entity
		void RemoveComponent(Entity entity)
		{
			const ComponentId* id = m_entityMap.GetComponent(entity);
			if (id == nullptr)
			{
				return;
			}
			ComponentId componentToMove = m_componentList.size - 1;
			m_componentList.data->at(*id) = m_componentList.data->at(componentToMove);
			Entity entityToMove = m_entityMap.GetEntity(componentToMove);

			m_entityMap.Delete(entity);

			if (entity.id != entityToMove.id) m_entityMap.Update(entityToMove, *id);

			m_componentList.size--;
		}

		// Returns the component, matching this managers type from the specified entity
		T* GetComponent(Entity entity) const
		{
			const ComponentId* id = m_entityMap.GetComponent(entity);
			if (id == nullptr)
			{
				return nullptr;
			}
			return &m_componentList.data->at(*id);
		}
		
		// Helper class, which is used to get the components of this manager, without
		// exposing its state too much
		class Iterator;

		Iterator* GetIterator() const
		{
			return new Iterator(&m_componentList);
		}

		class Iterator
		{
		public:
			ComponentList<T>* componentList;
			
			Iterator(ComponentList<T>* componentList)
			{
				this->componentList = componentList;
			}

			T* begin() const
			{
				return &componentList->data->at(0);
			}

			T* end() const
			{
				return &componentList->data->at(componentList->size);
			}
		};
	};
}