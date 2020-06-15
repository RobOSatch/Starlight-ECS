#include "GameObject.h"
#include "Renderer.h"
#include "GameLoop.h"

#include <Starlight.h>
#include "Components/TransformComponent.h"
#include "Systems/UpMoveSystem.h"
#include "Entity/ComponentContainer.h"

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

	//gameLoop.Run_FixedDeltaTime(renderer, go);
	//gameLoop.Run_VariableDeltaTime(renderer, go);
	//gameLoop.Run_SemiFixedDeltaTime(renderer, go);
	//gameLoop.Run_DecoupledV1(renderer, go);
	//gameLoop.Run_DecoupledV2(renderer, go);

	// Init some stuff (maybe refactor, this is kinda disgusting)
	std::unique_ptr<Starlight::EntityManager> entityManager = std::make_unique<Starlight::EntityManager>();
	Starlight::Engine* starlightEngine = new Starlight::Engine(std::move(entityManager));

	// Add systems
	Starlight::System* upMoveSystem = new UpMoveSystem();
	starlightEngine->AddSystem(upMoveSystem);

	// Initialize game
	starlightEngine->Init();

	TransformComponent component;
	component.m_Position = Vector2(0.0f, 0.0f);
	component.m_Rotation = Vector2(0.0f, 0.0f);
	component.m_Scale = Vector2(0.0f, 0.0f);
	
	// Add an entity
 	Starlight::Entity player = starlightEngine->CreateEntity();
	starlightEngine->AddComponent(player, TransformComponent(component));

	for(int i = 0; i < 100; i++)
	{		
		starlightEngine->Update(0.33f);
	}
	
	return 0;
}

