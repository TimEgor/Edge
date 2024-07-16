#pragma once

#define EDGE_TO_STRING(S) #S
#define EDGE_TO_STRING_DEF(DEF) EDGE_TO_STRING(DEF)
#define EDGE_TO_CHAR(C) #@C

#define EDGE_CONCAT(A, B) A##B
#define EDGE_CONCAT_DEF(A, B) EDGE_CONCAT(A, B)

#if defined(WIN32) || defined(_WIN32)
#define EDGE_FUNCTION_NAME	__FUNCTION__
#define EDGE_LINE			__LINE__
#define EDGE_COUNTER		__COUNTER__
#else
#define EDGE_FUNCTION_NAME	__func__
#define EDGE_LINE			__line__
#define EDGE_COUNTER		__counter__
#endif