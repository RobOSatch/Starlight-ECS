#pragma once

#include <Utils/TypeWrapper.h>

namespace Starlight{
	using SystemID = ObjectID;
	class ISystem
	{
	public:
		~ISystem();
		virtual void Create() = 0;		
		virtual void Update(float dt) = 0;

	protected:
		ISystem();
	private:
		SystemID m_SystemID;
	};
}
