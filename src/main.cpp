#include "Renderer.h"
#include <Starlight.h>

#include "Components/TransformComponent.h"
#include "Components/CircleComponent.h"
#include "Components/MouseInputComponent.h"

#include "Systems/UpMoveSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/PlayerMoveSystem.h"
#include "Systems/ParticleMoveSystem.h"

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
	Starlight::System* particleMoveSystem = new ParticleMoveSystem();
	Starlight::System* renderSystem = new RenderSystem(&renderer);
	starlightEngine->AddSystem(inputSystem);
	starlightEngine->AddSystem(playerMoveSystem);
	starlightEngine->AddSystem(renderSystem);
	starlightEngine->AddSystem(particleMoveSystem);

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
	mouseComponent.m_Position = component.m_Position;

	ParticleComponent particleC;
	particleC.triggerRadius = 100.0f;
	
	// Add entities
 	Starlight::Entity player = starlightEngine->CreateEntity();
	starlightEngine->AddComponent(player, TransformComponent(component));
	starlightEngine->AddComponent(player, RenderComponent(renderComponent));
	starlightEngine->AddComponent(player, MouseInputComponent(mouseComponent));
	
	// TODO: Do bitmasks, this is absolutely disgusting
	inputSystem->AddEntity(player);
	playerMoveSystem->AddEntity(player);
	renderSystem->AddEntity(player);

	srand(time(NULL));
	renderComponent.m_Radius = 3;
	
	renderComponent.m_Color = Color{ 0, 0, 255, 1 };
	for(int i = 0; i < 1000; ++i)
	{		
		// Add entities
 		Starlight::Entity particle = starlightEngine->CreateEntity();
		component.m_Position = Vector2(rand() % wndWidth, rand() % wndHeight);
		particleC.originalPos = component.m_Position;
		starlightEngine->AddComponent(particle, TransformComponent(component));
		starlightEngine->AddComponent(particle, RenderComponent(renderComponent));
		starlightEngine->AddComponent(particle, MouseInputComponent(mouseComponent));
		starlightEngine->AddComponent(particle, ParticleComponent(particleC));
		
		//TODO: Do bitmasks, this is absolutely disgusting 
		renderSystem->AddEntity(particle);
		inputSystem->AddEntity(particle);
		particleMoveSystem->AddEntity(particle);
	}
	
	while (true)
	{
		starlightEngine->Update(0.33f);
	}
	
	return 0;
}

