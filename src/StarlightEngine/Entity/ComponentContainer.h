
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <Utils/TypeWrapper.h>

namespace Starlight
{


	static const uint32_t MAX_COMPONENT_COUNT = 0x00FFFFFF;
	static const uint8_t  INDEX_BITS = 24;

	// Stores an 8 bit value and a 24bit generation value per slot
	template<size_t MAX_NUM_SLOTS>
	class IndexFreeList
	{
	public:

		IndexFreeList() :
			nextFreeIndex(0)
		{
			assert(MAX_NUM_SLOTS <= MAX_COMPONENT_COUNT); // Only works with 8 bit indices

			// Setup freelist: point to next free slot
			for (uint32_t i = 0; i < MAX_NUM_SLOTS; ++i)
			{
				slots[i] = i + 1;
			}
			slots[MAX_NUM_SLOTS - 1] = MAX_NUM_SLOTS - 1; // Last free entry is pointing to itself
		}

		// Get new slot index combined with its current generation
		uint32_t alloc()
		{
			assert(nextFreeIndex != MAX_NUM_SLOTS); // Out of free slots

			uint32_t freeIndex = nextFreeIndex;

			if (getSlotValue(nextFreeIndex) == nextFreeIndex) // Last free slot (pointing to itself)?
			{
				nextFreeIndex = MAX_NUM_SLOTS; // all slots are now occupied
			}
			else
			{
				nextFreeIndex = getSlotValue(nextFreeIndex);
			}

			// Increase generation of returned slot
			const uint32_t generation = getGeneration(freeIndex);

			return freeIndex | (generation << 8);
		}

		void free(uint32_t indexWithgeneration)
		{
			uint32_t index =(indexWithgeneration & 0x00FFFFFF);
			uint32_t generation = (indexWithgeneration & 0xFF000000) >> INDEX_BITS;

			// Check if generations match
			assert(getGeneration(index) == generation);

			// Add slot back to freelist

			if (nextFreeIndex == MAX_NUM_SLOTS)
			{
				// All slots currently occupied
				setSlotValue(index, index); // Point to itself
			}
			else
			{
				setSlotValue(index, nextFreeIndex);
			}

			// Increase generation of slot
			setGeneration(index, generation + 1);

			nextFreeIndex = index;
		}

		bool isValid(uint32_t indexWithgeneration) const
		{
			uint32_t index = (uint32_t)(indexWithgeneration & 0x00FFFFFF);
			uint32_t generation = (indexWithgeneration & 0xFF000000) >> INDEX_BITS;
			return getGeneration(index) == generation;
		}

		uint32_t getGeneration(uint32_t index) const
		{
			return (slots[index] & 0xFF000000) >> 8;
		}

		// Only allowed to call on previously allocated slots
		void setSlotValue(uint32_t slotIndex, uint32_t value)
		{
			slots[slotIndex] = (slots[slotIndex] & 0xFF000000) | value;
		}

		uint32_t getSlotValue(uint32_t slotIndex) const
		{
			return (uint32_t)(slots[slotIndex] & 0x00FFFFFF);
		}

	private:

		void setGeneration(uint32_t slotIndex, uint32_t generation)
		{
			assert((generation & 0xFF000000) == 0); // generation is only 24 bits
			slots[slotIndex] = (slots[slotIndex] & 0x00FFFFFF) | (generation << 8);
		}

		// first 8 bits are indices/values, the remaining 24 bits are the slot's generation
		uint32_t slots[MAX_NUM_SLOTS];
		uint32_t nextFreeIndex;
	};


	// in our exercise, the ComponentContainer only holds componentes, nothing more.
	// the ComponentContainer implementation makes sure that after *each* operation its internal data structure has no holes,
	// and contains Component instances which are stored contiguously in memory.
	template<class T>
	class ComponentContainer
	{
	public:
		ComponentContainer(void)
			: m_componentCount(0),
			m_componentToLookup{ 0 }
		{
		}


		// Needs to be O(1)
		ComponentID AddComponent(T component)
		{
			assert(m_componentCount < MAX_COMPONENT_COUNT);

			const uint32_t indexWithGeneration = m_lookup.alloc();
			const uint32_t lookupIndex = (uint32_t)(indexWithGeneration & 0x00FFFFFF);

			// Call constructor on m_componentes[m_componentCount]? => but would then also need dtor, copy ctor, assignment op,...
			// https://www.modernescpp.com/index.php/c-core-guidelines-constructors-assignments-and-desctructors
			// => I'm not calling ctor here

			// Map lookup index to component index
			const uint32_t componentIndex = (uint32_t)(m_componentCount & 0x00FFFFFF);
			m_componentes[componentIndex] = component;
			m_lookup.setSlotValue(lookupIndex, componentIndex);

			// Store reverse mapping for ::RemoveComponent
			m_componentToLookup[componentIndex] = lookupIndex;

			++m_componentCount;

			return static_cast<ComponentID>(indexWithGeneration);
		}


		// Needs to be O(1)
		void RemoveComponent(ComponentID id)
		{
			// TODO: add your implementation here.
			// thoroughly comment *what* you do, and *why* you do it (in german or english).

			assert(m_componentCount > 0);
			if (m_componentCount == 0)
				return;

			const uint32_t indexWithGeneration = static_cast<uint32_t>(id);
			assert(m_lookup.isValid(indexWithGeneration));

			const uint32_t index = (uint32_t)(indexWithGeneration & 0x00FFFFFF);
			uint32_t componentIndex = m_lookup.getSlotValue(index);

			// Keep m_componentes packed
			const uint32_t lookupIndex = m_componentToLookup[m_componentCount - 1];
			m_lookup.setSlotValue(lookupIndex, componentIndex);

			std::swap(m_componentes[componentIndex], m_componentes[m_componentCount - 1]);
			std::swap(m_componentToLookup[componentIndex], m_componentToLookup[m_componentCount - 1]);

			m_lookup.free(indexWithGeneration);
			--m_componentCount;
		}

		// Needs to be O(1)
		T* Lookup(ComponentID id)
		{
			// TODO: add your implementation here.
			// thoroughly comment *what* you do, and *why* you do it (in german or english).

			const uint32_t indexWithGeneration = static_cast<uint32_t>(id);
			if (m_lookup.isValid(indexWithGeneration))
			{
				const uint32_t index = (uint32_t)(indexWithGeneration & 0x00FFFFFF);
				uint32_t componentIndex = m_lookup.getSlotValue(index);
				return &m_componentes[componentIndex];
			}
			else
			{
				return nullptr;
			}
		}


		// DO NOT CHANGE!
		// the implementation of this method needs to stay as it is.
		// you need to correctly implement all other methods to ensure that:
		// a) m_componentCount is up-to-date
		// b) m_componentes stores instances of Component contiguously, without any holes
		// c) external ComponentIDs still refer to the correct instances somehow
		void Iterate(void)
		{
			for (unsigned int i = 0; i < m_componentCount; ++i)
			{
				//printf("Component instance %d: dummy = %d\n", i, m_componentes[i]);
			}
		}


	private:
		// TODO: add other data structures you may need

		IndexFreeList<MAX_COMPONENT_COUNT> m_lookup;
		uint32_t m_componentToLookup[MAX_COMPONENT_COUNT];

		// DO NOT CHANGE!
		// these two members are here to stay. see comments regarding Iterate().
		T m_componentes[MAX_COMPONENT_COUNT];
		uint32_t m_componentCount;
	};
}