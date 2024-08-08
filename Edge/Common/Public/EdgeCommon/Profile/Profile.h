#pragma once

#include "EdgeCommon/CommonMacros.h"

namespace Edge
{
	namespace Profile
	{
		class ProfileEvent final
		{
		public:
			ProfileEvent(const char* title, const char* context = nullptr);
			~ProfileEvent();
		};

		void beginEvent(const char* titleName, const char* contextName = nullptr);
		void endEvent();
	}
}

#ifndef EDGE_CONFIG_RETAIL
	#define EDGE_PROFILE_SCOPE_NAME(SCOPE) EDGE_CONCAT(profileEvent_, SCOPE)
	#define EDGE_PROFILE_GENERIC_SCOPE_NAME() EDGE_PROFILE_SCOPE_NAME(EDGE_COUNTER)

	#define EDGE_PROFILE_BEGIN_EVENT(TITLE) Edge::Profile::beginEvent(TITLE);
	#define EDGE_PROFILE_BEGIN_EVENT_CONTEXT(TITLE, CONTEXT) Edge::Profile::beginEvent(TITLE, CONTEXT);
	#define EDGE_PROFILE_END_EVENT() Edge::Profile::endEvent();

	#define EDGE_PROFILE_BLOCK_EVENT(TITLE) Edge::Profile::ProfileEvent EDGE_PROFILE_GENERIC_SCOPE_NAME()(TITLE);
	#define EDGE_PROFILE_BLOCK_EVENT_CONTEXT(TITLE, CONTEXT) Edge::Profile::ProfileEvent EDGE_PROFILE_GENERIC_SCOPE_NAME()(TITLE, CONTEXT);
	#define EDGE_PROFILE_FUNCTION() Edge::Profile::ProfileEvent(EDGE_FUNCTION_NAME);
#else
	#define EDGE_PROFILE_SCOPE_NAME(SCOPE)
	#define EDGE_PROFILE_GENERIC_SCOPE_NAME()

	#define EDGE_PROFILE_BEGIN_EVENT(TITLE)
	#define EDGE_PROFILE_BEGIN_EVENT_CONTEXT(TITLE, CONTEXT)
	#define EDGE_PROFILE_END_EVENT()

	#define EDGE_PROFILE_BLOCK_EVENT(TITLE)
	#define EDGE_PROFILE_BLOCK_EVENT_CONTEXT(TITLE, CONTEXT)
	#define EDGE_PROFILE_FUNCTION()
#endif
