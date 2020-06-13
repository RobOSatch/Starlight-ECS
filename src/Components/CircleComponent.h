#pragma once

#include <Starlight.h>

struct Color
{
	float r, g, b, a;
};

class CircleComponent : public Starlight::Component<CircleComponent>
{
private:
	Color m_Color;
	float m_Radius;

public:
	CircleComponent()
	{}

	CircleComponent(Color color, float radius)
		:
		m_Color(color),
		m_Radius(radius)
	{}

	~CircleComponent()
	{}

	void SetColor(Color color)
	{
		m_Color = color;
	}

	void SetRadius(float radius)
	{
		m_Radius = radius;
	}

	Color GetColor()
	{
		return m_Color;
	}

	float GetRadius()
	{
		return m_Radius;
	}


};

