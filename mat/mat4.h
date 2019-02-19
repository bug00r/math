#if 0
/**
	This ist a 4x4 matrix.
*/
#endif

#ifndef MAT_4_H
#define MAT_4_H

#include <stddef.h>

typedef struct {
	float _11, _12, _13,_14, _21, _22, _23, _24, _31, _32, _33, _34 , _41, _42, _43, _44;
} mat4_t;

extern const size_t mat4_size;

#if 0
/**
	Calculate determinant.
*/
#endif
float mat4_determinant( const mat4_t *  m);

#if 0
/**
	compares two mat4 matrix.
*/
#endif
bool mat4_equals( const mat4_t *  m, const mat4_t *  m2);

#if 0
/**
	Transponse matrix.
*/
#endif
void mat4_transponse( mat4_t *  m);

#if 0
/**
	Creates transponse from matrix m and creates a new result.
*/
#endif
mat4_t * mat4_transponse_new( const mat4_t *  m);

#if 0
/**
	Copies values from matrix m2 into m1.
	NOTE: You must free the string by yourself.
*/
#endif
void mat4_copy( mat4_t *  m, const mat4_t *  m2);

#if 0
/**
	Copies values from matrix m into new matrix.
	NOTE: You must free the string by yourself.
*/
#endif
mat4_t * mat4_copy_new( const mat4_t *   m);

#if 0
/**
	Creates string from mat4 coordinates.
*/
#endif
void mat4_print( const mat4_t *  m);

#if 0
/**
	Add two mat4 matrix and stores result in matrix m.
*/
#endif
void mat4_add( mat4_t *  m, const mat4_t *  m2);

#if 0
/**
	Add two mat4 matrix and stores result in new matrix and return.
*/
#endif
mat4_t * mat4_add_new( const mat4_t *  m, const mat4_t *  m2);

#if 0
/**
	Sub two mat4 matrix and stores result in matrix m.
*/
#endif
void mat4_sub( mat4_t *  m, const mat4_t *  m2);

#if 0
/**
	Sub two mat4 matrix and stores result in new matrix and return.
*/
#endif
mat4_t * mat4_sub_new( const mat4_t *  m, const mat4_t *  m2);

#if 0
/**
	Multiplies two mat4 matrix and stores result in matrix m.
*/
#endif
void mat4_mul( mat4_t *  m, const mat4_t *  m2);
void mat4_mul_dest( mat4_t *  dest, const mat4_t *  m, const mat4_t *  m2);

#if 0
/**
	Multiplies two mat4 matrix and stores result in new matrix and return.
*/
#endif
mat4_t * mat4_mul_new( const mat4_t *  m, const mat4_t *   m2);

#if 0
/**
	Multiplies mat4 matrix with skalar and stores result in matrix m.
*/
#endif
void mat4_mul_skalar( mat4_t *   m, const float skalar);

#if 0
/**
	Multiplies mat4 matrix with skalat and stores result in new matrix and return.
*/
#endif
mat4_t * mat4_mul_skalar_new( const mat4_t *   m, const float skalar);

#if 0
/**
	Calculates the inverse of a matrix and change value from given one.
*/
#endif
void mat4_inverse( mat4_t *   m);
void mat4_inverse_dest(mat4_t *  dest, const mat4_t *   m);

#if 0
/**
	Calculates the inverse of a matrix and returns result in a new matrix.
*/
#endif
mat4_t * mat4_inverse_new(const mat4_t *   m);

#endif