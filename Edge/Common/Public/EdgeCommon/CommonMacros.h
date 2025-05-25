#pragma once

#define EDGE_TO_STRING(s) #s
#define EDGE_TO_STRING_DEF(def) EDGE_TO_STRING(def)
#define EDGE_TO_CHAR(c) #@c

#define EDGE_CONCAT(a, b) a##b
#define EDGE_CONCAT_DEF(a, b) EDGE_CONCAT(a, b)

#if defined(WIN32) || defined(_WIN32)
#define EDGE_FUNCTION_NAME	__FUNCTION__
#define EDGE_FUNCTION_SIGNATURE_NAME	__FUNCSIG__
#define EDGE_LINE			__LINE__
#define EDGE_COUNTER		__COUNTER__
#else
#define EDGE_FUNCTION_NAME	__func__
#define EDGE_FUNCTION_SIGNATURE_NAME	__PRETTY_FUNCTION__ 
#define EDGE_LINE			__line__
#define EDGE_COUNTER		__counter__
#endif