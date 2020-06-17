<img src="https://i.imgur.com/FlxniCH.png" title="ECS Demo" alt="ECS Demo">

# Starlight Engine

> A simple Entity Component System

Some of the most helpful references used to create the ECS engine:
* <a href="https://medium.com/@savas/nomad-game-engine-part-1-why-3be9825cb90a">The Nomad Game Engine Blog</a>
* <a href="https://www.youtube.com/watch?v=W3aieHjyNvw&t=309s">GDC Talk about the gameplay architecture of Overwatch</a>
* <a href="https://www.youtube.com/watch?v=rX0ItVEVjHc">Talk from Mike Akton about Data Oriented Design
  
## External Libraries
The project uses SDL for its renderer. Other than that, no external libraries are being used.

## Setup
The project contains all required files to run it. Just open up the solution in Visual Studio for example, and run it.

## Demo
The demo for this project features a "player" entity (purple rectangle), which can be controlled by moving the mouse around. 10000 Particles (blue rectangles) are spawned will move away from the player, whenever they are near. Once the player leaves their trigger range, the particles will arrange themselves in their original positions.

![](https://media.giphy.com/media/f3GhE4SXoJrX3NMQvb/giphy.gif)

---
## The Entity Component System
The project uses an ECS to manage the game logic. Systems encapsulate behaviour and hold no data, while components hold data, but have no behaviour. Entities are there to group components, which likely will work together (player entity for example). The ECS makes use of efficient memory layout, by storing components of the same type contiguously in memory and allowing no "holes" in those memory blocks. The system's caching is setup in a way, where it will loop through those continous memory blocks during the update cycle. Despite the update cycle being called multiple times per second, the layout of the memory and its usage make it incredibly efficient, even when handling a large number of entities per frame. The following sections explain how to use the ECS.

## Using the engine
In order to use the engine you have to include `Starlight.h`. After that, you have to create an instance of `EntityManager` and use it to get an instance of `Engine`.
```
std::unique_ptr<EntityManager> entityManager = std::make_unique<EntityManager>();
Engine* starlightEngine = new Engine(std::move(entityManager));
```

## Adding systems
Before you initialize the engine propery, you need to add all your systems. This is done by calling `AddSystem`.
```
starlightEngine->AddSystem(mySystem);
starlightEngine->AddSystem(anotherSystem);
starlightEngine->Init();
```

## Component and Entity Manager
The entity manager is used to create new entities. Just call `starlightEngine->CreateEntity()` to get an entity object. After that you can add as many components as you want to your entity by calling `AddComponent`. If you want to get a specific component for a given entity, you can use the corresponding `ComponentManager` to do so.
```
// Create entity and add components
Entity player = starlightEngine->CreateEntity();
starlightEngine->AddComponent(player, TransformComponent(transformComponent));
starlightEngine->AddComponent(player, RenderComponent(renderComponent));

// Get the transform component of the player
auto* transform = starlightEngine->GetComponentManager<TransformComponent>()->GetComponent(player);
```

## Defining a component
Each component you define has to be derived from `Component`. You have to provide its own type as a generic parameter for the `ComponentManager` to register and manage it properly.
```
struct PositionComponent : public Component<PositionComponent>
{
  float x, y, z;
}
```

## Defining a system
Each system you define has to be derived from `System`. Additionally you have to provide a generic struct type, which will group the components used by the system
```
class MySystem : public Starlight::System<MyTuple>
```
The `System` class provides a couple of virtual functions you need to implement in order to use it. Those are `Init`, `MakeTuple` and `Update`.
`Init` is the place, where you specify the component types, which your system will "listen" for. Any entities, which hold the component types, registered within the sytem, will be used by the system during its update cycle.
`MakeTuple` takes an entity and extracts the components, which the sytem needs into a tuple (the struct you defined earlier).
`Update` is your systems update cycle, where you use and modify the components data. You can loop through all the tuples and do some logic here, while the `System` class will do all the caching, etc. for you.

```
struct MyTuple
{
  MyComponent* myComponent;
  AnotherComponent* anotherComponent;
}

class MySystem : public Starlight::System<MyTuple>
{
  void Init()
  {
    AddComponentType<MyComponent>();
    AddComponentType<AnotherComponent>();
  }
  
  MyTuple MakeTuple(Entity e)
  {
    auto* myC = engine->GetComponentManager<MyComponent>()->GetComponent(e);
    auto* aC = engine->GetComponentManager<AnotherComponent>()->GetComponent(e);
    
    return { myC, aC };
  }
  
  void Update(std::array<MyTuple, size>* tuples, float dt)
  {
    // Do some logic with tuples
  }
}
```

## Main game loop
After defining and setting up all the systems, components and entities, all there is left is to create the main loop for the program and calling the engines update function.
```
// main game loop
while (true)
{
  starlightEngine->Update(deltaTime);
}
```
---
# Our Team
* <a href="https://github.com/TheodorKnab">Theodor Knab</a>
* <a href="https://github.com/Prommerbua">Michael Prommer</a>
* <a href="https://github.com/RobOSatch">Robert Barta</a>

## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**
