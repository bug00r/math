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
} Mat3;

extern const size_t mat3_size;

#if 0
/**
	Calculate determinant.
*/
#endif
float mat3_determinant( const Mat3 *  m);

#if 0
/**
	compares two mat3 matrix.
*/
#endif
bool mat3_equals( const Mat3 *  m, const Mat3 *  m2);

#if 0
/**
	Transponse matrix.
*/
#endif
void Mat3ransponse( Mat3 *  m);

#if 0
/**
	Creates transponse from matrix m and creates a new result.
*/
#endif
Mat3 * Mat3ransponse_new( const Mat3 *  m);

#if 0
/**
	Copies values from matrix m2 into m1.
	NOTE: You must free the string by yourself.
*/
#endif
void mat3_copy( Mat3 *  m, const Mat3 *  m2);

#if 0
/**
	Copies values from matrix m into new matrix.
	NOTE: You must free the string by yourself.
*/
#endif
Mat3 * mat3_copy_new( const Mat3 *  m);

#if 0
/**
	Creates string from mat3 coordinates.
	NOTE: You must free the string by yourself.
*/
#endif
void mat3_print( const Mat3 *   m);

#if 0
/**
	Add two mat3 matrix and stores result in matrix m.
*/
#endif
void mat3_add( Mat3 *   m, const Mat3 *   m2);

#if 0
/**
	Add two mat3 matrix and stores result in new matrix and return.
*/
#endif
Mat3 * mat3_add_new( const Mat3 *   m, const Mat3 *  m2);

#if 0
/**
	Sub two mat3 matrix and stores result in matrix m.
*/
#endif
void mat3_sub( Mat3 *  m, const Mat3 *  m2);

#if 0
/**
	Sub two mat3 matrix and stores result in new matrix and return.
*/
#endif
Mat3 * mat3_sub_new( const Mat3 *  m, const Mat3 *  m2);

#if 0
/**
	Multiplies two mat3 matrix and stores result in matrix m.
*/
#endif
void mat3_mul( Mat3 *  m, const Mat3 *  m2);

#if 0
/**
	Multiplies two mat3 matrix and stores result in new matrix and return.
*/
#endif
Mat3 * mat3_mul_new( const Mat3 *  m, const Mat3 *  m2);
Mat3 * mat3_mul_dest(Mat3 * dest, const Mat3 *   m, const Mat3 *   m2);

#if 0
/**
	Multiplies mat3 matrix with skalar and stores result in matrix m.
*/
#endif
void mat3_mul_skalar( Mat3 *  m, const float skalar);

#if 0
/**
	Multiplies mat3 matrix with skalat and stores result in new matrix and return.
*/
#endif
Mat3 * mat3_mul_skalar_new( const Mat3 *  m, const float skalar);

#if 0
/**
	Calculates the inverse of a matrix and change value from given one.
*/
#endif
void mat3_inverse( Mat3 *  m);
void mat3_inverse_dest( Mat3 *   dest, const Mat3 *   m);
#if 0
/**
	Calculates the inverse of a matrix and returns result in a new matrix.
*/
#endif
Mat3 * mat3_inverse_new( const Mat3 *   m);

#endif