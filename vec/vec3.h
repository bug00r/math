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
} vec3_t;	

extern const size_t vec3_size;

#if 0
	//creates zero vector from v.
#endif
void vec3_zero(vec3_t *  dest);

#if 0
	//creates new zero vector from v.
#endif
vec3_t * vec3_zero_new();

#if 0
	//sets new values from vec3
#endif
void vec3_set_values(vec3_t *  dest, const float x, const float y, const float z);

#if 0
/**
	Compares components of vectors and address.
*/
#endif
bool vec3_equals( const vec3_t *   v, const vec3_t *   v2);

#if 0
/**
	Crossproduct from 3D Vector
*/
#endif
void vec3_cross( vec3_t *   v, const vec3_t *   v2);

#if 0
/**
	Crossproduct from 3D Vector
*/
#endif
vec3_t* vec3_cross_new( const vec3_t *   v, const vec3_t *   v2);
void vec3_cross_dest(vec3_t *  dest, const vec3_t *   v, const vec3_t *   v2);

#if 0
/**
	Multiplication from vector with skalar. Result saved in given vector.
*/
#endif
void vec3_mul( vec3_t *   v, const float skalar);

#if 0
/**
	Multiplication from vector with skalar. Result saved in given destination vector.
	return manipulated vector.
*/
#endif
vec3_t * vec3_mul_dest(vec3_t *  dest, const vec3_t *   v, const float skalar);

#if 0
/**
	Multiplication from vector with skalar. Result saved in new vector.
*/
#endif
vec3_t * vec3_mul_new( const vec3_t *   v, const float skalar);

#if 0
/**
	Multiplication from vector with vector2(Skalarproduct).
*/
#endif
float vec3_vec3mul( const vec3_t *   v, const vec3_t *   v2);

#if 0
/**
	Checks against orthogonality
*/
#endif
bool vec3_isorthogonal( const vec3_t *   v, const vec3_t *   v2);

#if 0
/**
	Spatproduct...means 3d Volume.
*/
#endif
float vec3_spat( const vec3_t *   v, const vec3_t *   v2, const vec3_t *   v3);

#if 0
/**
	Calculates length of Vector.
*/
#endif
float vec3_length( const vec3_t *   v);

#if 0
/**
	Creates a new Vector with values from old one.
*/
#endif
vec3_t * vec3_copy_new( const vec3_t *   v);

#if 0
/**
	Copies Vector data from v2 into dest and returns dest
*/
#endif
vec3_t * vec3_copy_dest( vec3_t *   dest, const vec3_t *   v2);

#if 0
/**
	Creates string from vec3 coordinates.
	NOTE: You must free the string by yourself.
*/
#endif
char * vec3_tostring( const vec3_t *   v);

#if 0
/**
	prints vec 3
*/
#endif
void vec3_print( const vec3_t *   v);

#if 0
/**
	tranforms v into -v and sores value in v
*/
#endif
void vec3_negate(vec3_t *   v);

#if 0
/**
	tranforms v into -v, stores in dest and return dest
*/
#endif
vec3_t * vec3_negate_dest(vec3_t *   dest, const vec3_t *   v);

#if 0
/**
	tranforms v into -v and sores value in new vector 
*/
#endif
vec3_t* vec3_negate_new(const vec3_t *   v);

#if 0
/**
	Vector addition. Result is saved in v1.
*/
#endif
void vec3_add( vec3_t *  v1,  const vec3_t *  v2);

#if 0
/**
	Vector addition. Result is saved in dest and returned dest.
*/
#endif
vec3_t * vec3_add_dest( vec3_t *  dest, const vec3_t *  v1,  const vec3_t *   v2);

#if 0
/**
	Vector addition. Result is saved new vector.
*/
#endif
vec3_t* vec3_add_new(  const vec3_t *   v1,  const vec3_t *  v2);

#if 0
/**
	Subtract multiple vectors from zero and stores result inside dest and returns dest
*/
#endif
vec3_t * vec3_add_n_dest(vec3_t *  dest, const int cntvecs, ...);

#if 0
/**
	Subtract multiple vectors from zero and stores result inside dest and returns as new vector
*/
#endif
vec3_t* vec3_add_n_new( const int cntvecs, ...);

#if 0
/**
	Vector difference. Result is saved in v1.
*/
#endif
void vec3_sub( vec3_t *  v1,  const vec3_t *  v2);

#if 0
/**
	Vector difference. Result is saved in v1.
*/
#endif
vec3_t * vec3_sub_dest( vec3_t *  dest, const vec3_t *  v1,  const vec3_t *   v2);

#if 0
/**
	Vector difference. Result is saved new vector.
*/
#endif
vec3_t* vec3_sub_new(  const vec3_t *   v1, const vec3_t *   v2);

#if 0
/**
	Subtract multiple vectors from zero and stores result inside dest and returns dest
*/
#endif
vec3_t * vec3_sub_n_dest(vec3_t *  dest, const int cntvecs, ...);

#if 0
/**
	Subtract multiple vectors from zero and stores result inside dest and returns as new vector
*/
#endif
vec3_t* vec3_sub_n_new( const int cntvecs, ...);

#if 0
/**
	Normalize a vector. Current Vector is normalized vector
*/
#endif
void vec3_normalize( vec3_t *   v);

#if 0
/**
	Normalize a vector, stores result in dest and returns dest
*/
#endif
vec3_t * vec3_normalize_dest( vec3_t *  dest, const vec3_t *   v);

#if 0
/**
	Normalize a vector. Returns new normalized vector.
*/
#endif
vec3_t * vec3_normalize_new( const vec3_t *   v);

#if 0
/**
	Angle between two vectors. returns cos from angle, must be converted with arccos to get complete Angle.
*/
#endif
float vec3_angle( const vec3_t *   v, const vec3_t *   v2);

#endif