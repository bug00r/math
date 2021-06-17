#ifndef UTILS_MATH_H
#define UTILS_MATH_H

#if 0
/**
	This is a utils lib for difference more or less elegance consolidated functions
*/
#endif


#include "vec.h"
#include "mat.h"

#include <stdlib.h>
#include <stdio.h>

#include <stdbool.h>
#include <complex.h>
#include <math.h>
#include <time.h>


typedef struct {
	float _Complex cpoint;
	float _Complex spoint;
	float abs;
	int iterations;
	bool isin;
} mandelbrot_point_t;

typedef struct {
	int iterations;
	bool isin;
	float _Complex cpoint;
	float _Complex spoint;
	float abs;
} julia_point_t;

typedef struct {
	float w0_12;
	float w1_20;
	float w2_01;
	float area;
	float bc0;
	float bc1;
	float bc2;
	bool inside;
} barycentric_t;

#if 0
	//lineare interpolation
#endif
float interpolate_lin(const float x, const float x0, const float f0, const float x1, const float f1);

#if 0
	//compare functions for float. Used in qaort algorithm
#endif
int compare_floats(const void * a, const void* b);

#if 0
	//calculates a pseudorandom number from lnum to hnum
#endif
float seedrndlh(const float lnum, const float hnum);

#if 0
	//calculates a pseudorandom number from 0 to seed
#endif
float seedrnd(const float seed);

#if 0
/**
	cals if point is inside mandelbrot set. Stores results inside of mandelbrot_point_t
*/
#endif
void inside_mandelbrot_set(const float _Complex *  point, const int cntiterations, mandelbrot_point_t *  result);

#if 0
/**
	cals if point is inside julia set. Stores results inside of julia_point_t
*/
#endif
void inside_julia_set(const float _Complex *  point, const float _Complex *  c, const int cntiterations, 
				      julia_point_t *  result, float _Complex (*polyfunc)(const float _Complex *  cp, const float _Complex *  c));
#if 0
/**
	calcs radian from degree
*/
#endif
float rad(const float degree);

#if 0
/**
	generates random path degree. NOT THREADSAFE USING => using rand()
*/
#endif
float rand_path_deg(const int maxdeg);

#if defined(USE_VEC_3)

#if 0
	//scales vector
#endif
vec3_t * vec3_scale_dest(vec3_t *  dest, const float scx, const float scy, const float scz);

#endif

#if defined(USE_VEC_2) && defined(USE_MAT_2)


#if 0
/**
	Matrix 2x2 multiplies with vec 2. Result stored in vector v
*/
#endif
void mat_vec_mul_2(const mat2_t *  m, vec2_t *  v);

#if 0
/**
	Matrix 2x2 multiplies with vec 2. Result stored in new result vector
*/
#endif
vec2_t * mat_vec_mul_2_new(const mat2_t *  m, const vec2_t *  v);

#if 0
/**
	Calculates the side which point is placed depend on direction vector.
	This is used by juan pinedas edge function.
	s = startvector
	e = endvector
	p = point
*/
#endif
float place_of_vec3(const vec3_t *  s, const vec3_t *  e, const vec3_t *  p);

#if 0
/**
	Checks if point is inside of triangle(edgeFunction from juan pineda).
	v0,v1,v2 = points of triangle
	p = point,
	if barycentric_coords is not null then there will be calculate and save the coodinates inside.
*/
#endif
void is_inside_triangle(const vec3_t *  v0, const vec3_t *  v1, const vec3_t *  v2, const vec3_t *  p, barycentric_t *  bc);
void print_barycentric(const barycentric_t *  bc);

float line_intersect_denominator(vec2_t* l1p1, vec2_t* l1p2, vec2_t* l2p1, vec2_t* l2p2);
bool lines_intersect(vec2_t* l1p1, vec2_t* l1p2, vec2_t* l2p1, vec2_t* l2p2);
bool lines_intersect_pt(vec2_t *intersec, vec2_t* l1p1, vec2_t* l1p2, vec2_t* l2p1, vec2_t* l2p2);

#endif

#if defined(USE_VEC_3) && defined(USE_MAT_3)

#if 0
/**
	Matrix 2x2 multiplies with vec 3. Result stored in vector v
*/
#endif
void mat_vec_mul_3(const mat3_t *  m, vec3_t *  v);

#if 0
/**
	Matrix 3x3 multiplies with vec 3. Result stored in new result vector
*/
#endif
vec3_t * mat_vec_mul_3_new(const mat3_t *  m, const vec3_t *  v);
vec3_t * mat_vec_mul_3_dest(vec3_t * dest, const mat3_t *  m, const vec3_t *  v);
#if 0
/**
	create roattion matrix for x axis.
*/
#endif
mat3_t * create_rot_x_mat(const float degree);
mat3_t * create_rot_x_mat_dest(mat3_t * dest, const float degree);

#if 0
/**
	create roattion matrix for y axis.
*/
#endif
mat3_t * create_rot_y_mat(const float degree);
mat3_t * create_rot_y_mat_dest(mat3_t * dest, const float degree);

#if 0
/**
	create roattion matrix for z axis.
*/
#endif
mat3_t * create_rot_z_mat(const float degree);
mat3_t * create_rot_z_mat_dest(mat3_t * dest, const float degree);
#endif

#if defined(USE_VEC_3) && defined(USE_MAT_4)

#if 0
/**
	Matrix 4X4 multiplies with vector, for 3D Point transformation.
	Result was stored in same vector.
*/
#endif
float transform_point(const mat4_t *  m, vec3_t *  v);

#if 0
/**
	Matrix 4X4 multiplies with vector, for 3D Point transformation.
	Result ist a new Vector.
*/
#endif
vec3_t * transform_point_new(const mat4_t *  m, const vec3_t *  v);
float transform_point_dest(vec3_t *  dest, const mat4_t *  m, const vec3_t *  v);

#if 0
	/*
		Calculates Distance from point to plane. Calculates normal vector intern.
		If you want to use a precomputet normal vector please use function:
			mu_point_plane_distance_normal
	*/
#endif
float mu_point_plane_distance(vec3_t *point, vec3_t *plane_p1, vec3_t *plane_p2, vec3_t *plane_p3);
float mu_point_plane_distance_normal(vec3_t *point, vec3_t *plane_point, vec3_t *normal);

bool mu_line_plane_intersection(vec3_t *intersect, vec3_t *line_p1, vec3_t *line_p2, vec3_t *plane_p1, vec3_t *plane_p2, vec3_t *plane_p3);
bool mu_line_plane_intersection_normal(vec3_t *intersect, vec3_t *line_p1, vec3_t *line_p2, vec3_t *plane_point, vec3_t *normal);

#endif
#endif
