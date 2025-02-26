#pragma once

#include "EdgeCommon/CommonMacros.h"
#include "EdgeCommon/Patterns/Singleton.h"

#include "AssertGenerator.h"

#include <cassert>

namespace Edge
{
	class AssertCore final : public Singleton<AssertCore>
	{
	private:
		AssertGenerator* m_generator = nullptr;

	public:
		AssertCore() = default;

		void setGenerator(AssertGenerator* generator) { m_generator = generator; }
		AssertGenerator* getGenerator() const { return m_generator; }
	};

	inline AssertGenerator* GetAssertGenerator() { return AssertCore::getInstance().getGenerator(); }
}

#if defined(EDGE_CONFIG_DEBUG) || defined(EDGE_CONFIG_RELEASE)
#define EDGE_ASSERT(condition)															\
	if (!(condition)) {																	\
		Edge::AssertGenerator* generator = Edge::GetAssertGenerator();					\
		if (generator)																	\
		{																				\
			generator->generateError(EDGE_TO_STRING(condition), __FILE__, __LINE__);	\
		}																				\
		else																			\
		{																				\
			assert(condition);															\
		}																				\
	}


#define EDGE_ASSERT_MESSAGE(condition, message)											\
	if (!(condition)) {																	\
		Edge::AssertGenerator* generator = Edge::GetAssertGenerator();					\
		if (generator)																	\
		{																				\
			generator->generateError(message, __FILE__, __LINE__);						\
		}																				\
		else																			\
		{																				\
			assert((condition) && (message));											\
		}																				\
	}

#define EDGE_ASSERT_FAIL()																\
	Edge::AssertGenerator* generator = Edge::GetAssertGenerator();						\
	if (generator)																		\
	{																					\
		generator->generateError("FAIL", __FILE__, __LINE__);							\
	}																					\
	else																				\
	{																					\
		assert(false);																	\
	}	

#define EDGE_ASSERT_FAIL_MESSAGE(message)												\
	Edge::AssertGenerator* generator = Edge::GetAssertGenerator();						\
	if (generator)																		\
	{																					\
		generator->generateError(message, __FILE__, __LINE__);							\
	}																					\
	else																				\
	{																					\
		assert(false && (message));														\
	}

#else
#define EDGE_ASSERT(condition)					((void)0)
#define EDGE_ASSERT_MESSAGE(condition, message)	((void)0)
#define EDGE_ASSERT_FAIL()						((void)0)
#define EDGE_ASSERT_FAIL_MESSAGE(message)		((void)0)
#endif