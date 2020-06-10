#pragma once

#include "Renderer.h"
#include "GameObject.h"
#include <algorithm>

class GameLoop
{
public:

	void Run_FixedDeltaTime(Renderer& renderer, GameObject& gameObject)
	{
		float dt = 1.0f / 30.0f;

		while (!renderer.ShouldExit())
		{
			gameObject.Update(dt);

			renderer.BeginFrame();
			Render(renderer, gameObject.GetState());
			renderer.EndFrame();
		}
	}

	void Run_VariableDeltaTime(Renderer& renderer, GameObject& gameObject)
	{
	}

	void Run_SemiFixedDeltaTime(Renderer& renderer, GameObject& gameObject)
	{
	}

	void Run_DecoupledV1(Renderer& renderer, GameObject& gameObject)
	{
	}

	void Run_DecoupledV2(Renderer& renderer, GameObject& gameObject)
	{
	}


private:

	static void Render(Renderer& renderer, const GameObjectState& state)
	{
		renderer.DrawRect((int)roundf(state.position.x), (int)roundf(state.position.y), 16, 16, 255, 0, 0);
	}
};