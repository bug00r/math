#if 0
/**
	This ist a 2x2 matrix.
*/
#endif

#ifndef MAT_2_H
#define MAT_2_H

#include <stddef.h>


typedef struct {
	float _11, _12, _21, _22;
} mat2_t;

extern const size_t mat2_size;

#if 0
/**
	Calculate determinant.
*/
#endif
float mat2_determinant( const mat2_t *  m);

#if 0
/**
	compares two mat2 matrix.
*/
#endif
bool mat2_equals( const mat2_t *  m, const mat2_t *  m2);

#if 0
/**
	Transponse matrix.
*/
#endif
void mat2_transponse( mat2_t *  m);

#if 0
/**
	Creates transponse from matrix m and creates a new result.
*/
#endif
mat2_t * mat2_transponse_new( const mat2_t *  m);

#if 0
/**
	Copies values from matrix m2 into m1.
	NOTE: You must free the string by yourself.
*/
#endif
void mat2_copy( mat2_t *  m, const mat2_t *  m2);

#if 0
/**
	Copies values from matrix m into new matrix.
	NOTE: You must free the string by yourself.
*/
#endif
mat2_t * mat2_copy_new(const mat2_t *  m);

#if 0
/**
	Creates string from mat2 coordinates.
	NOTE: You must free the string by yourself.
*/
#endif
void mat2_print( const mat2_t *   m);

#if 0
/**
	Add two mat2 matrix and stores result in matrix m.
*/
#endif
void mat2_add( mat2_t *   m, const mat2_t *   m2);

#if 0
/**
	Add two mat2 matrix and stores result in new matrix and return.
*/
#endif
mat2_t * mat2_add_new( const mat2_t *   m, const mat2_t *   m2);

#if 0
/**
	Sub two mat2 matrix and stores result in matrix m.
*/
#endif
void mat2_sub( mat2_t *   m, const mat2_t *   m2);

#if 0
/**
	Sub two mat2 matrix and stores result in new matrix and return.
*/
#endif
mat2_t * mat2_sub_new( const mat2_t *   m, const mat2_t *   m2);

#if 0
/**
	Multiplies two mat2 matrix and stores result in matrix m.
*/
#endif
void mat2_mul( mat2_t *   m, const mat2_t *   m2);

#if 0
/**
	Multiplies two mat2 matrix and stores result in new matrix and return.
*/
#endif
mat2_t * mat2_mul_new( const mat2_t *   m, const mat2_t *   m2);

#if 0
/**
	Multiplies mat2 matrix with skalar and stores result in matrix m.
*/
#endif
void mat2_mul_skalar( mat2_t *   m, const float skalar);

#if 0
/**
	Multiplies mat2 matrix with skalat and stores result in new matrix and return.
*/
#endif
mat2_t * mat2_mul_skalar_new( const mat2_t *   m, const float skalar);

#if 0
/**
	Calculates the inverse of a matrix and change value from given one.
*/
#endif
void mat2_inverse( mat2_t *   m);
void mat2_inverse_dest( mat2_t *  dest, const mat2_t *   m);
#if 0
/**
	Calculates the inverse of a matrix and returns result in a new matrix.
*/
#endif
mat2_t * mat2_inverse_new( const mat2_t *   m);

#endif