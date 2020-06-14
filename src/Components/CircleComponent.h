#pragma once

#include <Starlight.h>

struct Color
{
	float r, g, b, a;
};

struct RenderComponent : public Starlight::Component<RenderComponent>
{
public:
	Color m_Color;
	float m_Radius;
};

