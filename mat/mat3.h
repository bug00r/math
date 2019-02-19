#if 0
/**
	This ist a 3x3 matrix.
*/
#endif

#ifndef MAT_3_H
#define MAT_3_H

#include <stddef.h>

typedef struct {
	float _11, _12, _13, _21, _22, _23, _31, _32, _33;
} mat3_t;

extern const size_t mat3_size;

#if 0
/**
	Calculate determinant.
*/
#endif
float mat3_determinant( const mat3_t *  m);

#if 0
/**
	compares two mat3 matrix.
*/
#endif
bool mat3_equals( const mat3_t *  m, const mat3_t *  m2);

#if 0
/**
	Transponse matrix.
*/
#endif
void mat3_transponse( mat3_t *  m);

#if 0
/**
	Creates transponse from matrix m and creates a new result.
*/
#endif
mat3_t * mat3_transponse_new( const mat3_t *  m);

#if 0
/**
	Copies values from matrix m2 into m1.
	NOTE: You must free the string by yourself.
*/
#endif
void mat3_copy( mat3_t *  m, const mat3_t *  m2);

#if 0
/**
	Copies values from matrix m into new matrix.
	NOTE: You must free the string by yourself.
*/
#endif
mat3_t * mat3_copy_new( const mat3_t *  m);

#if 0
/**
	Creates string from mat3 coordinates.
	NOTE: You must free the string by yourself.
*/
#endif
void mat3_print( const mat3_t *   m);

#if 0
/**
	Add two mat3 matrix and stores result in matrix m.
*/
#endif
void mat3_add( mat3_t *   m, const mat3_t *   m2);

#if 0
/**
	Add two mat3 matrix and stores result in new matrix and return.
*/
#endif
mat3_t * mat3_add_new( const mat3_t *   m, const mat3_t *  m2);

#if 0
/**
	Sub two mat3 matrix and stores result in matrix m.
*/
#endif
void mat3_sub( mat3_t *  m, const mat3_t *  m2);

#if 0
/**
	Sub two mat3 matrix and stores result in new matrix and return.
*/
#endif
mat3_t * mat3_sub_new( const mat3_t *  m, const mat3_t *  m2);

#if 0
/**
	Multiplies two mat3 matrix and stores result in matrix m.
*/
#endif
void mat3_mul( mat3_t *  m, const mat3_t *  m2);

#if 0
/**
	Multiplies two mat3 matrix and stores result in new matrix and return.
*/
#endif
mat3_t * mat3_mul_new( const mat3_t *  m, const mat3_t *  m2);
mat3_t * mat3_mul_dest(mat3_t * dest, const mat3_t *   m, const mat3_t *   m2);

#if 0
/**
	Multiplies mat3 matrix with skalar and stores result in matrix m.
*/
#endif
void mat3_mul_skalar( mat3_t *  m, const float skalar);

#if 0
/**
	Multiplies mat3 matrix with skalat and stores result in new matrix and return.
*/
#endif
mat3_t * mat3_mul_skalar_new( const mat3_t *  m, const float skalar);

#if 0
/**
	Calculates the inverse of a matrix and change value from given one.
*/
#endif
void mat3_inverse( mat3_t *  m);
void mat3_inverse_dest( mat3_t *   dest, const mat3_t *   m);
#if 0
/**
	Calculates the inverse of a matrix and returns result in a new matrix.
*/
#endif
mat3_t * mat3_inverse_new( const mat3_t *   m);

#endif