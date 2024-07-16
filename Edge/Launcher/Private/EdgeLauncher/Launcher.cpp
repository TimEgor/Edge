#include "EdgeEngine/Core/PlatformMacros.h"

#include "EdgeEngine/EngineCore.h"
#include "EdgeEngine/Engine/IEngine.h"

#if defined(WIN32) || defined(_WIN32)
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Edge::EngineCore::getInstance().createEngine();

	Edge::IEngine& edgeEngine = Edge::GetEngine();

	if (edgeEngine.init(Edge::IEngine::InitData{}))
	{
		
		edgeEngine.release();
	}

	return 0;
}
#endif