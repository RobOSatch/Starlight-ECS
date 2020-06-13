#pragma once

#include <Starlight.h>
#include "../Vector2.h"

class TransformComponent : public Starlight::Component<TransformComponent>
{
private:
	Vector2 m_Position;
	Vector2 m_Rotation;
	Vector2 m_Scale;
	
public:
	TransformComponent()
		:
		m_Position(Vector2(0.0f, 0.0f)),
		m_Rotation(Vector2(0.0f, 0.0f)),
		m_Scale(Vector2(1.0f, 1.0f))
	{}

	TransformComponent(Vector2 position, Vector2 rotation, Vector2 scale)
		:
		m_Position(position),
		m_Rotation(rotation),
		m_Scale(scale)
	{}

	~TransformComponent()
	{}

	void SetPosition(Vector2 newPosition)
	{
		this->m_Position = newPosition;
	}

	void SetRotation(Vector2 newRotation)
	{
		this->m_Rotation = newRotation;
	}

	void SetScale(Vector2 newScale)
	{
		this->m_Scale = newScale;
	}

	Vector2 GetPosition()
	{
		return m_Position;
	}

	Vector2 GetRotation()
	{
		return m_Rotation;
	}

	Vector2 GetScale()
	{
		return m_Scale;
	}

};