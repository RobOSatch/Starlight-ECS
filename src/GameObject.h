#pragma once

#include "Vector2.h"
#include "Renderer.h"

class GameObjectState
{
public:
	GameObjectState(const GameObjectState& other) :
		position(other.position),
		velocity(other.velocity),
		acceleration(other.acceleration)
	{}

	GameObjectState(const Vector2& pos, const Vector2& vel, const Vector2& acc) :
		position(pos),
		velocity(vel),
		acceleration(acc)
	{}

	static GameObjectState Interpolate(const GameObjectState& a, const GameObjectState& b, float t)
	{
		const float tInv = 1.0f - t;
		return GameObjectState(
			b.position * t + a.position * tInv,
			b.velocity * t + a.velocity * tInv,
			b.acceleration * t + a.acceleration * tInv
		);
	}

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
};

class GameObject
{
public:

	GameObject(const Vector2& pos, const Vector2& vel, const Vector2& acc, float _floorY) :
		state(pos, vel, acc),
		floorY(_floorY)
	{}

	void Update(float deltaTimeSec)
	{
		state.velocity += state.acceleration * deltaTimeSec;
		state.position += state.velocity * deltaTimeSec;

		if (state.position.y <= 0)
		{
			state.position.y = 0;
			state.velocity.y *= -0.5f;
			state.velocity.x *= 0.75f;
		}
		else if (state.position.y >= floorY)
		{
			state.position.y = floorY;
			state.velocity.y *= -0.5f;
			state.velocity.x *= 0.75f;
		}
	}

	const GameObjectState& GetState() const
	{
		return state;
	}

private:

	GameObjectState state;
	float floorY;
};