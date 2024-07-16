#pragma once

#ifdef TS_MATH_DX
#define TS_MATH_SET
#endif

#ifndef TS_MATH_SET
#if defined(WIN32) || defined(_WIN32)
#define TS_MATH_DX
#define TS_MATH_SET
#endif
#endif