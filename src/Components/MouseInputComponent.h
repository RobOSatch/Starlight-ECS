#pragma once
#include <Starlight.h>
#include "../Vector2.h"

class MouseInputComponent : Starlight::Component<MouseInputComponent>
{
private:
	Vector2 m_Position;

public:
	MouseInputComponent()
		:
		m_Position(Vector2(0.0f, 0.0f))
	{}

	~MouseInputComponent()
	{
	}

	void SetPosition(Vector2 position)
	{
		m_Position = position;
	}

	Vector2 GetPosition()
	{
		return this->m_Position;
	}
};

