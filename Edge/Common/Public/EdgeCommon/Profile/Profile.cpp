#include "Profile.h"

#if !defined(EDGE_CONFIG_RETAIL)
	#ifdef EDGE_PROFILE_PIX
		#include "Windows.h"

		#define USE_PIX
		#include "WinPixEventRuntime/pix3.h"
	#endif

	#ifdef EDGE_PROFILE_SUPERLUMINAL
		#include "Superluminal/PerformanceAPI.h"
	#endif
#endif

Edge::Profile::ProfileEvent::ProfileEvent(const char* title, const char* context)
{
	beginEvent(title, context);
}

Edge::Profile::ProfileEvent::~ProfileEvent()
{
	endEvent();
}

void Edge::Profile::beginEvent(const char* titleName, const char* contextName)
{
#if !defined(EDGE_CONFIG_RETAIL)
#ifdef EDGE_PROFILE_PIX
	PIXBeginEvent(PIX_COLOR_DEFAULT, "%s: %s", titleName, contextName ? contextName : "");
#endif
#ifdef EDGE_PROFILE_SUPERLUMINAL
	PerformanceAPI_BeginEvent(titleName, contextName, PERFORMANCEAPI_DEFAULT_COLOR);
#endif
#endif
}

void Edge::Profile::endEvent()
{
#if !defined(EDGE_CONFIG_RETAIL)
#ifdef EDGE_PROFILE_SUPERLUMINAL
	PerformanceAPI_EndEvent();
#endif

#ifdef EDGE_PROFILE_PIX
	PIXEndEvent();
#endif
#endif
}
