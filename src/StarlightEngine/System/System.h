#pragma once
#include <Component/Component.h>
#include <System/ISystem.h>

namespace Starlight
{
	template<class T>
	class System : public ISystem
	{
	private:
		//SystemManager* m_SystemManagerInstance;
	public:
		virtual void Update(float timeStep) = 0;
	};
}
