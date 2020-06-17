#pragma once

#include <Component/Component.h>
#include <Entity/Entity.h>
#include <Entity/EntityMap.h>

#include <array>
#include <map>

namespace Starlight
{
	class Engine;
	
	template<typename T>
	struct ComponentList
	{
		size_t size = 0;
		std::array<T, MAX_COMPONENTS>* data;
	};

	class IComponentManager
	{
	public:
		IComponentManager() = default;
		virtual ~IComponentManager() = default;

	};

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

		
		ComponentId AddComponent(Entity entity, T& component)
		{
			ComponentId id = m_componentList.size;
			m_componentList.data->at(id) = component;
			m_componentList.size++;
			m_entityMap.Add(entity, id);

			return id;
		}

		void RemoveComponent(Entity entity)
		{
			ComponentId id = m_entityMap.GetComponent(entity);

			ComponentId componentToMove = m_componentList.size - 1;
			m_componentList.data->at(id) = m_componentList.data->at(componentToMove);
			Entity entityToMove = m_entityMap.GetEntity(componentToMove);

			m_entityMap.Delete(entity);

			if (entity.id != entityToMove.id) m_entityMap.Update(entityToMove, id);

			m_componentList.size--;
		}

		T* GetComponent(Entity entity) const
		{
			ComponentId id = m_entityMap.GetComponent(entity);
			return &m_componentList.data->at(id);
		}
		

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