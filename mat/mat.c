#if 0
/**
	Basic implementation of 2x2,3x3,4x4 matrix.
*/	
#endif

#include "mat.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef USE_MAT_2
	#include "mat2.c"
#endif

#ifdef USE_MAT_3
	#include "mat3.c"
#endif

#ifdef USE_MAT_4
	#include "mat4.c"
#endif