#pragma once

#include "EdgeEngine/Core/Patterns/Singleton.h"

namespace Edge
{
	class IEngine;

	class EngineCore final : public Singleton<EngineCore>
	{
	private:
		IEngine* m_engine = nullptr;
		bool m_isEngineOwner = false;

	public:
		EngineCore() = default;

		bool createEngine();
		void destroyEngine();

		IEngine& getEngine() const;
		void setEngine(IEngine* engine); //Must be called before getEngine()
	};

	inline IEngine& GetEngine() { return EngineCore::getInstance().getEngine(); }
}
