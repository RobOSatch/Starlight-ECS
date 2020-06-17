#include "Renderer.h"
#include <Starlight.h>

#include "Components/TransformComponent.h"
#include "Components/CircleComponent.h"
#include "Components/MouseInputComponent.h"
#include "Components/TagComponent.h"

#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/PlayerMoveSystem.h"
#include "Systems/ParticleMoveSystem.h"

#include <time.h>
#include <omp.h>
#include <string>
#include <chrono>
#include <Windows.h>

#define FPS_INTERVAL 1.0 //seconds.

//***************************************************************************
//
// GED - Exercise 4 - Entity Component System
// by: Robert Barta, Theodor Knab, Michael Prommer
//
// **************************************************************************

int main(int argc, char* argv[])
{
	const size_t wndWidth = 1280;
	const size_t wndHeight = 720;

	Renderer renderer(wndWidth, wndHeight);

	Starlight::Engine* starlightEngine = new Starlight::Engine();

	// Create systems
	Starlight::ISystem* inputSystem = new InputSystem();
	Starlight::ISystem* playerMoveSystem = new PlayerMoveSystem();
	Starlight::ISystem* particleMoveSystem = new ParticleMoveSystem();
	Starlight::ISystem* renderSystem = new RenderSystem(&renderer);

	//Register systems
	starlightEngine->AddSystem(inputSystem);
	starlightEngine->AddSystem(playerMoveSystem);
	starlightEngine->AddSystem(particleMoveSystem);
	starlightEngine->AddSystem(renderSystem);

	// Register component managers
	starlightEngine->CreateComponentManager<TransformComponent>();
	starlightEngine->CreateComponentManager<RenderComponent>();
	starlightEngine->CreateComponentManager<ParticleComponent>();
	starlightEngine->CreateComponentManager<TagComponent>();

	// Setup components
	TransformComponent component;
	component.m_Position = Vector2(0.0f, 0.0f);
	
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
	starlightEngine->AddComponent(player, TagComponent(playerTag));
		
	renderComponent.m_Radius = 2;
	std::vector<Starlight::Entity> particlesToKill;
	
	renderComponent.m_Color = Color{ 0, 0, 255, 1 };

	for(int i = 0; i < 10000; ++i)
	{
		// Add entities
 		Starlight::Entity particle = starlightEngine->CreateEntity();
		component.m_Position = Vector2(16 * (i % 200), 8 * (i / 100));
		particleC.originalPos = component.m_Position;
		starlightEngine->AddComponent(particle, TransformComponent(component));
		starlightEngine->AddComponent(particle, RenderComponent(renderComponent));
		starlightEngine->AddComponent(particle, ParticleComponent(particleC));
	}
	
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point lastFrame = std::chrono::high_resolution_clock::now();


	Uint32 fps_lasttime = SDL_GetTicks(); //the last recorded time.
	Uint32 fps_current; //the current FPS.
	Uint32 fps_frames = 0; //frames passed since the last recorded fps.

	bool systemToggle = false;
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

