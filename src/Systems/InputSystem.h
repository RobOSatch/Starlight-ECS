#pragma once
#include <Starlight.h>
#include <../Components/MouseInputComponent.h>
#include <iostream>
#include <System/System.h>
#include <SDL.h>

MouseInputComponent* singletonInput;

struct InputTuple
{
};

//reads the input to a singleton component
class InputSystem : public Starlight::System<InputTuple>
{
	void Init()
	{
	}
	
	// Not needed because singleton
	InputTuple MakeTuple(Starlight::Entity e)
	{
		return {};
	}

	void Update(std::array<InputTuple, 0x000FFFFF>* tuples, float dt)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		Vector2 pos;
		pos.x = x;
		pos.y = y;

		singletonInput->m_Position = pos;
	}
};