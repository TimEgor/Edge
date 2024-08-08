#pragma once

#include "EdgeCommon/Patterns/Singleton.h"

namespace Edge
{
	class Physics;

	class PhysicsCore final : public Singleton<PhysicsCore>
	{
	private:
		Physics* m_physics = nullptr;

	public:
		PhysicsCore() = default;

		bool initPhysics();
		void releasePhysics();

		Physics* getPhysics() const;
		
		void copyState(const PhysicsCore& core); //used for dynamic loaded plugins
	};

	Physics& GetPhysics();
}
