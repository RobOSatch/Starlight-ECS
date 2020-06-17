#pragma once
#include "Component.h"

namespace Starlight {

    // This struct represents a bitmask, which is used to match systems and entities
    // depending on the component types they are using. If an entity has the components,
    // which a system is "listening" for, they are "matched"
    struct ComponentTypeBitmask {
        unsigned int m_bitmask = 0;

        template <typename C>
        void AddComponent() {
            m_bitmask |= (1 << GetComponentTypeId<C>());
        }

        template <typename C>
        void RemoveComponent() {
            m_bitmask &= ~(1 << GetComponentTypeId<C>());
        }

        bool IsNowMatched(ComponentTypeBitmask oldBitmask, ComponentTypeBitmask systemBitmask) const
        {
            return (*this == systemBitmask) && !(oldBitmask == systemBitmask);
        }

        bool IsNowUnmatched(ComponentTypeBitmask oldBitmask, ComponentTypeBitmask systemBitmask) const
        {
            return (oldBitmask == systemBitmask) && (*this != systemBitmask);
        }

        bool operator==(ComponentTypeBitmask rhs) const
        {
            return ((m_bitmask & rhs.m_bitmask) == rhs.m_bitmask);
        }

        bool operator!=(ComponentTypeBitmask rhs) const
        {
            return !(*this == rhs);
        }
    };
}