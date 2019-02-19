#if 0
/**
	Basic implementation of 2d or 3d vector. Following feature are implemented:
		2D	3D		Description
		---------------------------
		(X)	(X)		create vectors
		(X)	(X)		add
		(X)	(X) 	sub
		(X)	(X) 	negate
		(X)	(X) 	copy
		(X)	(X) 	length
		(X)	(X) 	mul(Skalar)
		(X)	(X) 	normalize
		(X)	(X)		skalarproduct(mul with vector)
		(X)	(X)		crossproduct
		(-)	(X)		spatproduct
		
*/	
#endif

#include "vec.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef USE_VEC_2
	#include "vec2.c"
#endif

#ifdef USE_VEC_3
	#include "vec3.c"
#endif