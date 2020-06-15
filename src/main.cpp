#include "Renderer.h"
#include <Starlight.h>

#include "Components/TransformComponent.h"
#include "Components/CircleComponent.h"
#include "Components/MouseInputComponent.h"

#include "Systems/UpMoveSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/PlayerMoveSystem.h"

#include "Entity/ComponentContainer.h"

#include <time.h>

int main(int argc, char* argv[])
{

	const size_t wndWidth = 1280;
	const size_t wndHeight = 720;

	Renderer renderer(wndWidth, wndHeight);

	// Init some stuff (maybe refactor, this is kinda disgusting)
	std::unique_ptr<Starlight::EntityManager> entityManager = std::make_unique<Starlight::EntityManager>();
	Starlight::Engine* starlightEngine = new Starlight::Engine(std::move(entityManager));

	// Add systems
	Starlight::System* upMoveSystem = new UpMoveSystem();
	Starlight::System* inputSystem = new InputSystem();
	Starlight::System* playerMoveSystem = new PlayerMoveSystem();
	Starlight::System* renderSystem = new RenderSystem(&renderer);
	starlightEngine->AddSystem(inputSystem);
	starlightEngine->AddSystem(playerMoveSystem);
	starlightEngine->AddSystem(renderSystem);

	// Initialize game
	starlightEngine->Init();

	// Setup components
	TransformComponent component;
	component.m_Position = Vector2(0.0f, 0.0f);
	component.m_Rotation = Vector2(0.0f, 0.0f);
	component.m_Scale = Vector2(0.0f, 0.0f);
	
	RenderComponent renderComponent;
	renderComponent.m_Color = Color{ 255, 0, 255, 1 };
	renderComponent.m_Radius = 25;

	MouseInputComponent mouseComponent;
	
	// Add entities
 	Starlight::Entity player = starlightEngine->CreateEntity();
	starlightEngine->AddComponent(player, TransformComponent(component));
	starlightEngine->AddComponent(player, RenderComponent(renderComponent));
	starlightEngine->AddComponent(player, MouseInputComponent(mouseComponent));
	
	//TODO: Do bitmasks, this is absolutely disgusting
	inputSystem->AddEntity(&player);
	playerMoveSystem->AddEntity(&player);
	renderSystem->AddEntity(&player);

	srand(time(NULL));
	renderComponent.m_Radius = 5;	
	for(int i = 0; i < 100; ++i)
	{		
		// Add entities
 		Starlight::Entity particle = starlightEngine->CreateEntity();
		
		TransformComponent componentParticle;
		componentParticle.m_Rotation = Vector2(0.0f, 0.0f);
		componentParticle.m_Scale = Vector2(0.0f, 0.0f);
		componentParticle.m_Position = Vector2(i, i);
		starlightEngine->AddComponent(particle, TransformComponent(componentParticle));
		starlightEngine->AddComponent(particle, RenderComponent(renderComponent));
		
		//TODO: Do bitmasks, this is absolutely disgusting 
		renderSystem->AddEntity(&particle);
	}	

	
	while (true)
	{
		starlightEngine->Update(0.33f);
		SDL_Delay(0.33f);
	}
	
	return 0;
}

