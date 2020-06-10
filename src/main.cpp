#include "GameObject.h"
#include "Renderer.h"
#include "GameLoop.h"


int main(int argc, char* argv[])
{
	const size_t wndWidth = 640;
	const size_t wndHeight = 480;
	const float gravityY = 9.81f * 2;

	const float floorY = wndHeight - 16;
	GameObject go(
		Vector2(16, floorY),
		Vector2(30, -380),
		Vector2(0, gravityY),
		floorY
	);

	GameLoop gameLoop;
	Renderer renderer(wndWidth, wndHeight);

	gameLoop.Run_FixedDeltaTime(renderer, go);
	//gameLoop.Run_VariableDeltaTime(renderer, go);
	//gameLoop.Run_SemiFixedDeltaTime(renderer, go);
	//gameLoop.Run_DecoupledV1(renderer, go);
	//gameLoop.Run_DecoupledV2(renderer, go);

	return 0;
}

