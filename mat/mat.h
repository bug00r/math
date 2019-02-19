#if 0
/**
	This ist the main matrix api header file and should be used in the project.
	Sure you can use mat2/3/4.h a directly but then you can't use the prepared
	config switches
*/
#endif

#ifndef MAT_H
#define MAT_H

#include <stdbool.h>

#include "mat_config.h"

#ifdef USE_MAT_2
	#include "mat2.h"
#endif

#ifdef USE_MAT_3
	#include "mat3.h"
#endif

#ifdef USE_MAT_4
	#include "mat4.h"
#endif

#endif