#pragma once

#ifdef EDGE_MATH_DX
#define EDGE_MATH_SET
#endif

#ifndef EDGE_MATH_SET
#if defined(WIN32) || defined(_WIN32)
#define EDGE_MATH_DX
#define EDGE_MATH_SET
#endif
#endif