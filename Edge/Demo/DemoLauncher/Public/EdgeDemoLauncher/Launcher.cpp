#include "EdgeCommon/PlatformMacros.h"

#include "EdgeDemoFramework/DemoApplication/DemoApplication.h"
#include "EdgeFramework/FrameworkCore.h"

#if defined(WIN32) || defined(_WIN32)
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	EdgeDemo::DemoApplication demoApplication;
	Edge::FrameworkCore::getInstance().setApplication(&demoApplication);

	if (demoApplication.init())
	{
		demoApplication.run();
		demoApplication.release();
	}

	return 0;
}
#endif