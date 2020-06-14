#pragma once
#include <bitset>
#include <vector>
#include <Entity/Entity.h>

namespace Starlight
{	
	class Engine;

	class System
	{		
	public:
		System() = default;
		virtual ~System() = default;

		virtual void Init() {};

		void RegisterEngine(Engine* engine)
		{
			this->engine = engine;
		}

		virtual void Update(float dt) = 0;

	protected:
		Engine* engine;
	};
}
