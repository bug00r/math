#if 0
/**
	This ist a vector with three dimensions x, y and z.
*/
#endif

#ifndef VEC_3_H
#define VEC_3_H

#include <stddef.h>

typedef struct {
	float x;
	float y;
	float z;
} Vec3;	

extern const size_t vec3_size;

#if 0
	//creates zero vector from v.
#endif
void vec3_zero(Vec3 *  dest);

#if 0
	//creates new zero vector from v.
#endif
Vec3 * vec3_zero_new();

#if 0
	//sets new values from vec3
#endif
void vec3_set_values(Vec3 *  dest, const float x, const float y, const float z);

#if 0
/**
	Compares components of vectors and address.
*/
#endif
bool vec3_equals( const Vec3 *   v, const Vec3 *   v2);

#if 0
/**
	Crossproduct from 3D Vector
*/
#endif
void vec3_cross( Vec3 *   v, const Vec3 *   v2);

#if 0
/**
	Crossproduct from 3D Vector
*/
#endif
Vec3* vec3_cross_new( const Vec3 *   v, const Vec3 *   v2);
void vec3_cross_dest(Vec3 *  dest, const Vec3 *   v, const Vec3 *   v2);

#if 0
/**
	Multiplication from vector with skalar. Result saved in given vector.
*/
#endif
void vec3_mul( Vec3 *   v, const float skalar);

#if 0
/**
	Multiplication from vector with skalar. Result saved in given destination vector.
	return manipulated vector.
*/
#endif
Vec3 * vec3_mul_dest(Vec3 *  dest, const Vec3 *   v, const float skalar);

#if 0
/**
	Multiplication from vector with skalar. Result saved in new vector.
*/
#endif
Vec3 * vec3_mul_new( const Vec3 *   v, const float skalar);

#if 0
/**
	Multiplication from vector with vector2(Skalarproduct).
*/
#endif
float vec3_vec3mul( const Vec3 *   v, const Vec3 *   v2);

#if 0
/**
	Checks against orthogonality
*/
#endif
bool vec3_isorthogonal( const Vec3 *   v, const Vec3 *   v2);

#if 0
/**
	Spatproduct...means 3d Volume.
*/
#endif
float vec3_spat( const Vec3 *   v, const Vec3 *   v2, const Vec3 *   v3);

#if 0
/**
	Calculates length of Vector.
*/
#endif
float vec3_length( const Vec3 *   v);

#if 0
/**
	Creates a new Vector with values from old one.
*/
#endif
Vec3 * vec3_copy_new( const Vec3 *   v);

#if 0
/**
	Copies Vector data from v2 into dest and returns dest
*/
#endif
Vec3 * vec3_copy_dest( Vec3 *   dest, const Vec3 *   v2);

#if 0
/**
	Creates string from vec3 coordinates.
	NOTE: You must free the string by yourself.
*/
#endif
char * Vec3ostring( const Vec3 *   v);

#if 0
/**
	prints vec 3
*/
#endif
void vec3_print( const Vec3 *   v);

#if 0
/**
	tranforms v into -v and sores value in v
*/
#endif
void vec3_negate(Vec3 *   v);

#if 0
/**
	tranforms v into -v, stores in dest and return dest
*/
#endif
Vec3 * vec3_negate_dest(Vec3 *   dest, const Vec3 *   v);

#if 0
/**
	tranforms v into -v and sores value in new vector 
*/
#endif
Vec3* vec3_negate_new(const Vec3 *   v);

#if 0
/**
	Vector addition. Result is saved in v1.
*/
#endif
void vec3_add( Vec3 *  v1,  const Vec3 *  v2);

#if 0
/**
	Vector addition. Result is saved in dest and returned dest.
*/
#endif
Vec3 * vec3_add_dest( Vec3 *  dest, const Vec3 *  v1,  const Vec3 *   v2);

#if 0
/**
	Vector addition. Result is saved new vector.
*/
#endif
Vec3* vec3_add_new(  const Vec3 *   v1,  const Vec3 *  v2);

#if 0
/**
	Subtract multiple vectors from zero and stores result inside dest and returns dest
*/
#endif
Vec3 * vec3_add_n_dest(Vec3 *  dest, const int cntvecs, ...);

#if 0
/**
	Subtract multiple vectors from zero and stores result inside dest and returns as new vector
*/
#endif
Vec3* vec3_add_n_new( const int cntvecs, ...);

#if 0
/**
	Vector difference. Result is saved in v1.
*/
#endif
void vec3_sub( Vec3 *  v1,  const Vec3 *  v2);

#if 0
/**
	Vector difference. Result is saved in v1.
*/
#endif
Vec3 * vec3_sub_dest( Vec3 *  dest, const Vec3 *  v1,  const Vec3 *   v2);

#if 0
/**
	Vector difference. Result is saved new vector.
*/
#endif
Vec3* vec3_sub_new(  const Vec3 *   v1, const Vec3 *   v2);

#if 0
/**
	Subtract multiple vectors from zero and stores result inside dest and returns dest
*/
#endif
Vec3 * vec3_sub_n_dest(Vec3 *  dest, const int cntvecs, ...);

#if 0
/**
	Subtract multiple vectors from zero and stores result inside dest and returns as new vector
*/
#endif
Vec3* vec3_sub_n_new( const int cntvecs, ...);

#if 0
/**
	Normalize a vector. Current Vector is normalized vector
*/
#endif
void vec3_normalize( Vec3 *   v);

#if 0
/**
	Normalize a vector, stores result in dest and returns dest
*/
#endif
Vec3 * vec3_normalize_dest( Vec3 *  dest, const Vec3 *   v);

#if 0
/**
	Normalize a vector. Returns new normalized vector.
*/
#endif
Vec3 * vec3_normalize_new( const Vec3 *   v);

#if 0
/**
	Angle between two vectors. returns cos from angle, must be converted with arccos to get complete Angle.
*/
#endif
float vec3_angle( const Vec3 *   v, const Vec3 *   v2);

#endif