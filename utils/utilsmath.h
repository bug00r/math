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
} MandelbrotPoint;

typedef struct {
	int iterations;
	bool isin;
	float _Complex cpoint;
	float _Complex spoint;
	float abs;
} JuliaPoint;

typedef struct {
	float w0_12;
	float w1_20;
	float w2_01;
	float area;
	float bc0;
	float bc1;
	float bc2;
	bool inside;
} Barycentric;

int round_f(float num);

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
	cals if point is inside mandelbrot set. Stores results inside of MandelbrotPoint
*/
#endif
void inside_mandelbrot_set(const float _Complex *  point, const int cntiterations, MandelbrotPoint *  result);

#if 0
/**
	cals if point is inside julia set. Stores results inside of JuliaPoint
*/
#endif
void inside_julia_set(const float _Complex *  point, const float _Complex *  c, const int cntiterations, 
				      JuliaPoint *  result, float _Complex (*polyfunc)(const float _Complex *  cp, const float _Complex *  c));
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
Vec3 * vec3_scale_dest(Vec3 *  dest, const float scx, const float scy, const float scz);

#endif

#if defined(USE_VEC_2) && defined(USE_MAT_2)


#if 0
/**
	Matrix 2x2 multiplies with vec 2. Result stored in vector v
*/
#endif
void mat_vec_mul_2(const Mat2 *  m, Vec2 *  v);

#if 0
/**
	Matrix 2x2 multiplies with vec 2. Result stored in new result vector
*/
#endif
Vec2 * mat_vec_mul_2_new(const Mat2 *  m, const Vec2 *  v);

#if 0
/**
	Calculates the side which point is placed depend on direction vector.
	This is used by juan pinedas edge function.
	s = startvector
	e = endvector
	p = point
*/
#endif
float place_of_vec3(const Vec3 *  s, const Vec3 *  e, const Vec3 *  p);

#if 0
/**
	Checks if point is inside of triangle(edgeFunction from juan pineda).
	v0,v1,v2 = points of triangle
	p = point,
	if barycentric_coords is not null then there will be calculate and save the coodinates inside.
*/
#endif
void is_inside_triangle(const Vec3 *  v0, const Vec3 *  v1, const Vec3 *  v2, const Vec3 *  p, Barycentric *  bc);
void print_barycentric(const Barycentric *  bc);

float line_intersect_denominator(Vec2* l1p1, Vec2* l1p2, Vec2* l2p1, Vec2* l2p2);
bool lines_intersect(Vec2* l1p1, Vec2* l1p2, Vec2* l2p1, Vec2* l2p2);
bool lines_intersect_pt(Vec2 *intersec, Vec2* l1p1, Vec2* l1p2, Vec2* l2p1, Vec2* l2p2);

bool lineseg_intersect(Vec2* l1p1, Vec2* l1p2, Vec2* l2p1, Vec2* l2p2);
bool lineseg_intersect_pt(Vec2 *intersec, Vec2* l1p1, Vec2* l1p2, Vec2* l2p1, Vec2* l2p2);

#endif

#if defined(USE_VEC_3) && defined(USE_MAT_3)

#if 0
/**
	Matrix 3x3 multiplies with vec 3. Result stored in vector v
*/
#endif
void mat_vec_mul_3(const Mat3 *  m, Vec3 *  v);

#if 0
/**
	Matrix 3x3 multiplies with vec 3. Result stored in new result vector
*/
#endif
Vec3 * mat_vec_mul_3_new(const Mat3 *  m, const Vec3 *  v);
Vec3 * mat_vec_mul_3_dest(Vec3 * dest, const Mat3 *  m, const Vec3 *  v);
#if 0
/**
	create rotation matrix for x axis.
*/
#endif
Mat3 * create_rot_x_mat(const float degree);
Mat3 * create_rot_x_mat_dest(Mat3 * dest, const float degree);

#if 0
/**
	create roattion matrix for y axis.
*/
#endif
Mat3 * create_rot_y_mat(const float degree);
Mat3 * create_rot_y_mat_dest(Mat3 * dest, const float degree);

#if 0
/**
	create roattion matrix for z axis.
*/
#endif
Mat3 * create_rot_z_mat(const float degree);
Mat3 * create_rot_z_mat_dest(Mat3 * dest, const float degree);
#endif

#if defined(USE_VEC_3) && defined(USE_MAT_4)

#if 0
/**
	Matrix 4X4 multiplies with vector, for 3D Point transformation.
	Result was stored in same vector.
*/
#endif
float transform_point(const Mat4 *  m, Vec3 *  v);

#if 0
/**
	Matrix 4X4 multiplies with vector, for 3D Point transformation.
	Result ist a new Vector.
*/
#endif
Vec3 * transform_point_new(const Mat4 *  m, const Vec3 *  v);
float transform_point_dest(Vec3 *  dest, const Mat4 *  m, const Vec3 *  v);

#if 0
	/*
		Calculates Distance from point to plane. Calculates normal vector intern.
		If you want to use a precomputet normal vector please use function:
			mu_point_plane_distance_normal
	*/
#endif
float mu_point_plane_distance(Vec3 *point, Vec3 *plane_p1, Vec3 *plane_p2, Vec3 *plane_p3);
float mu_point_plane_distance_normal(Vec3 *point, Vec3 *plane_point, Vec3 *normal);

bool mu_line_plane_intersection(Vec3 *intersect, Vec3 *line_p1, Vec3 *line_p2, Vec3 *plane_p1, Vec3 *plane_p2, Vec3 *plane_p3);
bool mu_line_plane_intersection_normal(Vec3 *intersect, Vec3 *line_p1, Vec3 *line_p2, Vec3 *plane_point, Vec3 *normal);

float polygon_area_2D(Vec2 *points, size_t cntPoints);
bool polygon_2D_is_clockwise(Vec2 *points, size_t cntPoints);

#endif
#endif
