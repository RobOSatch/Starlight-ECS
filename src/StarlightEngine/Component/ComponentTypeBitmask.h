#pragma once
#include "Component.h"

namespace Starlight {
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

        bool IsNowMatched(ComponentTypeBitmask oldBitmask, ComponentTypeBitmask systemBitmask)
        {
            return (*this == systemBitmask) && !(oldBitmask == systemBitmask);
        }

        bool IsNowUnmatched(ComponentTypeBitmask oldBitmask, ComponentTypeBitmask systemBitmask)
        {
            return (oldBitmask == systemBitmask) && (*this != systemBitmask);
        }

        bool operator==(ComponentTypeBitmask rhs)
        {
            return ((m_bitmask & rhs.m_bitmask) == rhs.m_bitmask);
        }

        bool operator!=(ComponentTypeBitmask rhs)
        {
            return !(*this == rhs);
        }
    };
}