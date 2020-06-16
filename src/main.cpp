#include "Renderer.h"
#include <Starlight.h>

#include "Components/TransformComponent.h"
#include "Components/CircleComponent.h"
#include "Components/MouseInputComponent.h"
#include "Components/TagComponent.h"

#include "Systems/UpMoveSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/PlayerMoveSystem.h"
#include "Systems/ParticleMoveSystem.h"

#include "Entity/ComponentContainer.h"

#include <time.h>
#include <omp.h>
#include <string>
#include < chrono >
#include <Windows.h>

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
	singletonInput = &mouseComponent;

	ParticleComponent particleC;
	particleC.triggerRadius = 90.0f;

	TagComponent playerTag;
	playerTag.tag = 0;
	
	// Add entities
 	Starlight::Entity player = starlightEngine->CreateEntity();
	starlightEngine->AddComponent(player, TransformComponent(component));
	starlightEngine->AddComponent(player, RenderComponent(renderComponent));
	//starlightEngine->AddComponent(player, MouseInputComponent(mouseComponent));
	starlightEngine->AddComponent(player, TagComponent(playerTag));

	Starlight::Entity mouse = starlightEngine->CreateEntity();
	//starlightEngine->AddComponent(mouse, MouseInputComponent(mouseComponent));
	
	// TODO: Do bitmasks, this is absolutely disgusting
	//inputSystem->AddEntity(player);
	//playerMoveSystem->AddEntity(player);
	//renderSystem->AddEntity(player);

	srand(time(NULL));
	renderComponent.m_Radius = 5;
	
	renderComponent.m_Color = Color{ 0, 0, 255, 1 };
	for(int i = 0; i < 10000; ++i)
	{
		// Add entities
 		Starlight::Entity particle = starlightEngine->CreateEntity();
		component.m_Position = Vector2(rand() % wndWidth, rand() % wndHeight);
		//component.m_Position = Vector2((i) % wndWidth, ((i * 5) % wndWidth * 5) % wndHeight);
		particleC.originalPos = component.m_Position;
		starlightEngine->AddComponent(particle, TransformComponent(component));
		starlightEngine->AddComponent(particle, RenderComponent(renderComponent));
		//starlightEngine->AddComponent(particle, MouseInputComponent(mouseComponent));
		starlightEngine->AddComponent(particle, ParticleComponent(particleC));
		
		//TODO: Do bitmasks, this is absolutely disgusting 
		//renderSystem->AddEntity(particle);
		//inputSystem->AddEntity(particle);
		//particleMoveSystem->AddEntity(particle);
	}
	
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point lastFrame = std::chrono::high_resolution_clock::now();

#define FPS_INTERVAL 1.0 //seconds.

	Uint32 fps_lasttime = SDL_GetTicks(); //the last recorded time.
	Uint32 fps_current; //the current FPS.
	Uint32 fps_frames = 0; //frames passed since the last recorded fps.

	while (true)
	{
		now = std::chrono::high_resolution_clock::now();
		int delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrame).count();
		lastFrame = now;

		starlightEngine->Update(delta);

		fps_frames++;
		if (fps_lasttime < SDL_GetTicks() - FPS_INTERVAL * 1000)
		{
			fps_lasttime = SDL_GetTicks();
			fps_current = fps_frames;
			fps_frames = 0;
			SDL_SetWindowTitle(renderer.getWindow(), std::to_string(fps_current).c_str());

		}
	}
	
	return 0;
}

