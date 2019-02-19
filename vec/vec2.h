#if 0
/**
	This ist a vector with two dimensions x and y.
*/
#endif

#ifndef VEC_2_H
#define VEC_2_H

#include <stddef.h>

typedef struct {
	float x, y;
} vec2_t;

extern const size_t vec2_size;

#if 0
	//creates zero vector from v.
#endif
void vec2_zero(vec2_t *  dest);

#if 0
	//creates new zero vector from v.
#endif
vec2_t * vec2_zero_new();

#if 0
/**
	Compares components of vectors and address. returns 0 if fails or 1
*/
#endif
bool vec2_equals( const vec2_t *   v, const vec2_t *   v2);

#if 0
/**
	Crossproduct from 2D Vector results a skalar
*/
#endif
float vec2_cross( const vec2_t *   v, const vec2_t *   v2);

#if 0
/**
	Multiplication from vector with skalar. Result saved in given vector.
*/
#endif
void vec2_mul( vec2_t *   v, const float skalar);

#if 0
/**
	Multiplication from vector with skalar. Result saved in given destination vector.
	return manipulated vector.
*/
#endif
vec2_t * vec2_mul_dest(vec2_t *  dest, const vec2_t *   v, const float skalar);

#if 0
/**
	Multiplication from vector with skalar. Result saved in new vector.
*/
#endif
vec2_t * vec2_mul_new( const vec2_t *   v, const float skalar);

#if 0
/**
	Multiplication from vector with vector2(Skalarproduct).
*/
#endif
float vec2_vec2mul( const vec2_t *   v, const vec2_t *   v2);

#if 0
/**
	Checks against orthogonality
*/
#endif
bool vec2_isorthogonal( const vec2_t *   v, const vec2_t *   v2);

#if 0
/**
	Calculates length of Vector.
*/
#endif
float vec2_length( const vec2_t *   v);

#if 0
/**
	Creates a new Vector with values from old one.
*/
#endif
vec2_t * vec2_copy_new( const vec2_t *   v);

#if 0
/**
	copy values from v into dest and return pointer to dest
*/
#endif
vec2_t * vec2_copy_dest(vec2_t *   dest, const vec2_t *   v);

#if 0
/**
	Creates string from vec2 coordinates.
	NOTE: You must free the string by yourself.
*/
#endif
char * vec2_tostring( const vec2_t *   v);

#if 0
/**
	prints vec2.
*/
#endif
void vec2_print( const vec2_t *   v);

#if 0
/**
	tranforms v into -v and sores value in v
*/
#endif
void vec2_negate(vec2_t *   v);

#if 0
/**
	tranforms v into -v ,stores value in dest and returns dest
*/
#endif
vec2_t * vec2_negate_dest(vec2_t *   dest, const vec2_t *   v);

#if 0
/**
	tranforms v into -v and sores value in new vector 
*/
#endif
vec2_t* vec2_negate_new(const vec2_t *   v);

#if 0
/**
	Vector addition. Result is saved in v1.
*/
#endif
void vec2_add( vec2_t *  v1,  const vec2_t *   v2);

#if 0
/**
	Vector addition. Result is saved in dest and returning dest.
*/
#endif
vec2_t * vec2_add_dest(vec2_t *  dest, const vec2_t *  v1,  const vec2_t *   v2);

#if 0
/**
	Vector addition. Result is saved new vector.
*/
#endif
vec2_t* vec2_add_new( const vec2_t *   v1, const vec2_t *   v2);

#if 0
/**
	Add multiple vectors and stores result inside dest and returns dest
*/
#endif
vec2_t * vec2_add_n_dest(vec2_t *  dest, const int cntvecs, ...);

#if 0
/**
	Add multiple vectors and stores result inside dest and returns as new vector
*/
#endif
vec2_t* vec2_add_n_new( const int cntvecs, ...);

#if 0
/**
	Vector difference. Result is saved in v1.
*/
#endif
void vec2_sub( vec2_t *v1,  const vec2_t *   v2);

#if 0
/**
	Vector difference. Result is saved in dest and returning dest.
*/
#endif
vec2_t * vec2_sub_dest(vec2_t *  dest, const vec2_t *  v1, const vec2_t *  v2);

#if 0
/**
	Vector difference. Result is saved new vector.
*/
#endif
vec2_t* vec2_sub_new(  const vec2_t *  v1,  const vec2_t *  v2);

#if 0
/**
	Subtract multiple vectors from zero and stores result inside dest and returns dest
*/
#endif
vec2_t * vec2_sub_n_dest(vec2_t *  dest, const int cntvecs, ...);

#if 0
/**
	Subtract multiple vectors from zero and stores result inside dest and returns as new vector
*/
#endif
vec2_t* vec2_sub_n_new( const int cntvecs, ...);

#if 0
/**
	Normalize a vector. Current Vector is normalized vector
*/
#endif
void vec2_normalize( vec2_t *  v);

#if 0
/**
	Normalize a vector, saved result in dest and return dest
*/
#endif
vec2_t * vec2_normalize_dest(vec2_t *  dest, const vec2_t *  v);

#if 0
/**
	Normalize a vector. Returns new normalized vector.
*/
#endif
vec2_t * vec2_normalize_new( const vec2_t *  v);

#if 0
/**
	Angle between two vectors. returns cos from angle, must be converted with arccos to get complete Angle.
*/
#endif
float vec2_angle( const vec2_t *  v, const vec2_t *  v2);


#endif