#if 0
/**
	This ist the main vec api header file and should be used in the project.
	Sure you can use vec2/3.ha directly but then you can't use the prepared
	config switches
*/
#endif

#ifndef VEC_H
#define VEC_H

#include <stdbool.h>

#include <stdarg.h>

#include "vec_config.h"

#ifndef M_PI
	#define M_PI 3.14159265358979323846264338327
#endif

#ifdef USE_VEC_2
	#include "vec2.h"
#endif

#ifdef USE_VEC_3
	#include "vec3.h"
#endif

#endif