#if 0
/**
	This is a Test programm for math utils
*/
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include "utilsmath.h"

int 
main() {
	#ifdef debug
		printf("Start testing math utils :\n");
	#endif
	
	#if 0
		//test randomseed limits
	#endif
	srand(time(NULL));
	
	#ifdef debug
		printf("random numbers from 0 - 10\n");
	#endif
	
	float rlh = seedrndlh(0.f, 10.f);
	
	#ifdef debug
		printf("-> %f\n", rlh);
	#endif
	assert(rlh >= 0.f && rlh <= 10.f);
	
	rlh = seedrndlh(0.f, 10.f);
	
	#ifdef debug
		printf("-> %f\n", rlh);
	#endif
	assert(rlh >= 0.f && rlh <= 10.f);
	
	rlh = seedrndlh(0.f, 10.f);
	
	#ifdef debug
		printf("-> %f\n", rlh);
	#endif
	assert(rlh >= 0.f && rlh <= 10.f);
	
	rlh = seedrndlh(0.f, 10.f);

	#ifdef debug
		printf("-> %f\n", rlh);
	#endif
	assert(rlh >= 0.f && rlh <= 10.f);
	
	rlh = seedrndlh(-10.f, 10.f);

	#ifdef debug
		printf("-> %f\n", rlh);
	#endif
	assert(rlh >= -10.f && rlh <= 10.f);
	
	rlh = seedrndlh(-10.f, 10.f);

	#ifdef debug
		printf("-> %f\n", rlh);
	#endif
	assert(rlh >= -10.f && rlh <= 10.f);
	
	rlh = seedrndlh(-10.f, 10.f);

	#ifdef debug
		printf("-> %f\n", rlh);
	#endif
	assert(rlh >= -10.f && rlh <= 10.f);
	
	rlh = seedrndlh(-10.f, 10.f);

	#ifdef debug
		printf("-> %f\n", rlh);
	#endif
	assert(rlh >= -10.f && rlh <= 10.f);
	
	//################
	
	int rlh_int = seedrndlh(0, 10);
	
	#ifdef debug
		printf("-> %i\n", rlh_int);
	#endif
	assert(rlh_int >= 0 && rlh_int <= 10);
	
	rlh_int = seedrndlh(0, 10);
	
	#ifdef debug
		printf("-> %i\n", rlh_int);
	#endif
	assert(rlh_int >= 0 && rlh_int <= 10);
	
	rlh_int = seedrndlh(0, 10);
	
	#ifdef debug
		printf("-> %i\n", rlh_int);
	#endif
	assert(rlh_int >= 0 && rlh_int <= 10);
	
	rlh_int = seedrndlh(0, 10);

	#ifdef debug
		printf("-> %i\n", rlh_int);
	#endif
	assert(rlh_int >= 0 && rlh_int <= 10);
	
	rlh_int = seedrndlh(-10, 10);

	#ifdef debug
		printf("-> %i\n", rlh_int);
	#endif
	assert(rlh_int >= -10 && rlh_int <= 10);
	
	rlh_int = seedrndlh(-10, 10);

	#ifdef debug
		printf("-> %i\n", rlh_int);
	#endif
	assert(rlh_int >= -10 && rlh_int <= 10);
	
	rlh_int = seedrndlh(-10, 10);

	#ifdef debug
		printf("-> %i\n", rlh_int);
	#endif
	assert(rlh_int >= -10 && rlh_int <= 10);
	
	rlh_int = seedrndlh(-10, 10);

	#ifdef debug
		printf("-> %i\n", rlh_int);
	#endif
	assert(rlh_int >= -10 && rlh_int <= 10);
	
	//################
	#if defined(USE_VEC_2) && defined(USE_MAT_2)
	
	#if 0
		/**
			test matrix multiply with vector
		*/
	#endif
	Mat2 mat2 = { 1.f, 2.f, 3.f, 4.f};
	Vec2 vec2 = { 2.f, 3.f};
	Vec2 vec2_result = { 8.f, 18.f};
	
	Vec2 * vec2_result_new = mat_vec_mul_2_new(&mat2, &vec2);
	assert(vec2_equals(vec2_result_new, &vec2_result));
	
	free(vec2_result_new);
	
	mat_vec_mul_2(&mat2, &vec2);
	assert(vec2_equals(&vec2, &vec2_result));
	
	#if 0
		/**
			test place of point
		*/
	#endif
	
	Vec3 start = {0.f, 0.f, 0.f};
	Vec3 end = {2.f, 2.f, 0.f};
	Vec3 point = {0.5f, 1.5f, 0.f};
	
	float place = place_of_vec3(&start, &end, &point);
	assert(place < 0.f);
	
	start = (Vec3) {0.f, 0.f, 0.f};
	end = (Vec3) {2.f, 2.f, 0.f};
	point = (Vec3){1.5f, 0.5f, 0.f};
	
	place = place_of_vec3(&start, &end, &point);
	assert( place > 0.f);
	
	start = (Vec3){0.f, 0.f, 0.f};
	end = (Vec3){2.f, 2.f, 0.f};
	point = (Vec3){1.f, 1.f, 0.f};
	
	place = place_of_vec3(&start, &end, &point);
	Vec3 *testdiff = vec3_sub_new(&point, &start);
	assert(place == 0.f && testdiff->x >= 0.f && testdiff->y >= 0.f);
	free(testdiff);
	start = (Vec3){0.f, 0.f, 0.f};
	end = (Vec3){2.f, 2.f, 0.f};
	point = (Vec3){-1.f, -1.f, 0.f};
	
	place = place_of_vec3(&start, &end, &point);
	testdiff = vec3_sub_new(&point, &start);
	assert(place == 0.f && testdiff->x < 0.f && testdiff->y < 0.f);
	
	#if 0
		/**
			test if point is inside or outside triangle
		*/
	#endif
	
	Vec3 v0 = {0.f, 0.f, 0.f};
	Vec3 v1 = {2.f, 2.f, 0.f};
	Vec3 v2 = {2.f, 0.f, 0.f};
	Vec3 point_ = {1.5f, .5f, 0.f};
	
	Barycentric bc;
	bc.area = place_of_vec3(&v0, &v1, &v2); 
	
	is_inside_triangle(&v0, &v1, &v2, &point_, &bc);
	assert(bc.inside);
	
	point_ = (Vec3){1.f, 1.f, 0.f};
	
	is_inside_triangle(&v0, &v1, &v2, &point_, &bc);
	assert(bc.inside);
	
	point_ = (Vec3){5.f, 1.f, 0.f};
	
	is_inside_triangle(&v0, &v1, &v2, &point_, &bc);
	assert(!bc.inside);
	
	point_ = (Vec3){1.f, 1.f, 0.f};
	
	is_inside_triangle(&v0, &v1, &v2, &point_, &bc);
	
	assert(bc.inside);
	
	#if 0
		/** Debug tests
			vec3(x=140.800003, y=115.199997, z=-1.500000)
			vec3(x=125.866669, y=140.800003, z=-1.500000)
			vec3(x=113.066666, y=115.199997, z=-1.500000)
		*/
	#endif
	
	v0 = (Vec3){140.800003f, 115.199997f, -1.500000f};
	v1 = (Vec3){125.866669f, 140.800003f, -1.500000f};
	v2 = (Vec3){113.066666f, 115.199997f, -1.500000f};
	point_ = (Vec3){130.5f, 110.f, 0.f};
	
	#if 0
		/**
			summary of barycentric coordinates must be 1 :)
		*/
	#endif
	
	assert((bc.bc0 + bc.bc1 + bc.bc2) == 1.f);
	
	#if 0
		/**
			special barycentric test from:
			https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/visibility-problem-depth-buffer-depth-interpolation
			
			which produces invalid result for a line example.
		*/
	#endif
		
	Vec3 spv0 = {0.f, 0.f,0.f}; //absolut 0 world coordinate
	Vec3 spv1 = {-2.f, 1.f,0.f}; //V0'
	Vec3 spv2 = {.4f, 1.f,0.f}; //V1'
	Vec3 sppoint_ = {0.f, 1.f,0.f}; //P'
	
	Barycentric spbcc;
	spbcc.area = place_of_vec3(&spv0, &spv1, &spv2);
	
	is_inside_triangle(&spv0, &spv1, &spv2, &sppoint_, &spbcc);
	
	#ifdef debug
		printf("spbcc: %f %f %f\n", spbcc.bc0, spbcc.bc1, spbcc.bc2 );
	#endif
	
	#if 0
		//P.z=V0.z*(1−λ)+V1.z∗*λ =2*1.666+5*0.833=4.5
	#endif
	float Pz = ((2*1)-(2*spbcc.bc2)) + (5*spbcc.bc2);
	#ifdef debug
		printf("P.z: %f == 4.5\n", Pz);
	#endif
	
	assert(Pz == 4.5f);
	
	#if 0
		/**
			special barycentric test from:
			https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/visibility-problem-depth-buffer-depth-interpolation
			
			which produces CORRECT RESULT result for a line.
			
			This is for a triangle: 1/P.z=1/V0.z*λ0+1/V1.z*λ1+1/V2.z*λ2.
		*/
	#endif
	
	Pz = (((1./2)*1)-((1./2)*spbcc.bc2)) + ((1./5)*spbcc.bc2);
	#ifdef debug
		printf("1/P.z: %f == 0.25 and P.z %f == 4\n", Pz, 1./Pz);
	#endif
	
	assert(Pz == .25f);
	assert(1./Pz == 4.f);
	#endif
			
	#if defined(USE_VEC_3) && defined(USE_MAT_3)
	
	#if 0
		/**
			test matrix multiply with vector
		*/
	#endif
	
	Mat3 mat3 = { 1.f, 0.f, 2.f, 0.f, 0.f, 4.f, 1.f, -1.f, 1.f};
	Vec3 vec3 = { 2.f, 2.f, 0.f};
	Vec3 vec3_result = { 2.f, 0.f, 0.f};
	
	Vec3 * vec3_result_new = mat_vec_mul_3_new(&mat3, &vec3);
	assert(vec3_equals(vec3_result_new, &vec3_result));
	
	free(vec3_result_new);
	
	mat_vec_mul_3(&mat3, &vec3);
	assert(vec3_equals(&vec3, &vec3_result));
	
	#endif
	
	/*
		Vec3 temp = {
		(v->x * m->_11) + (v->y * m->_21) + (v->z * m->_31) + m->_41,
		(v->x * m->_12) + (v->y * m->_22) + (v->z * m->_32) + m->_42,
		(v->x * m->_13) + (v->y * m->_23) + (v->z * m->_33) + m->_43
	};
	float weight = (v->x * m->_14) + (v->y * m->_24) + (v->z * m->_34) + m->_44;
	*/
	
	#if 0
		/**
			point transformation HAS CHANGED...NEW TEST NEED
		*/
	#endif
	
	//Mat4 Mat4rans = { 1.f, 2.f, 3.f, 0.f, 1.f, 2.f, 3.f, 0.f, 1.f, 2.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f};
	//Vec3 Vec3rans = { 2.f, 2.f, 2.f};
	//Vec3 vec3_result_trans = { 6.f, 12.f, 18.f};
	//
	//Vec3 *transformed = transform_point_new(&Mat4rans, &Vec3rans);
	//assert(vec3_equals(transformed, &vec3_result_trans));
	//
	//free(transformed);
	//
	//transform_point(&Mat4rans, &Vec3rans);
	//assert(vec3_equals(&Vec3rans, &vec3_result_trans));
	//
	//Mat4rans = (Mat4) { 1.f, 2.f, 3.f, 0.5f, 1.f, 2.f, 3.f, 0.5f, 1.f, 2.f, 3.f, 0.5f, 0.f, 0.f, 0.f, 1.f};
	//Vec3rans = (Vec3) { 2.f, 2.f, 2.f};
	//vec3_result_trans = (Vec3) { (6.f/4.), (12.f/4.), (18.f/4.)};
	//
	//transform_point(&Mat4rans, &Vec3rans);
	//assert(vec3_equals(&Vec3rans, &vec3_result_trans));
	
		
	float degree = 0.f;
	float radian = rad(degree);
	#ifdef debug
		const char * degfmt = "degree: %f rad: %f\n";
		printf(degfmt, degree, radian);
	#endif
	
	assert(radian == 0.f);
	
	degree = 30.f;
	radian = rad(degree);
	#ifdef debug
		printf(degfmt, degree, radian);
	#endif
	assert(radian == 0.5235987756f);
	
	degree = 45.f;
	radian = rad(degree);
	#ifdef debug
		printf(degfmt, degree, radian);
	#endif
	assert(radian == 0.7853981634f);
	
	degree = 150.f;
	radian = rad(degree);
	#ifdef debug
		printf(degfmt, degree, radian);
	#endif
	assert(radian == 2.6179938780f);
	
	#if defined(USE_VEC_3) && defined(USE_MAT_3)
	
	#if 0
		/**
			test matrix multiply with vector
		*/
	#endif
	
	Mat3 * rotx_mat = create_rot_x_mat(90.f);
	Mat3 * roty_mat = create_rot_y_mat(90.f);
	Mat3 * rotz_mat = create_rot_z_mat(90.f);
	
	Vec3 vec31 = { 1.f, 0.f, 0.f};
	Vec3 vec32 = { 1.f, 0.f, 0.f};
	Vec3 vec33 = { 1.f, 0.f, 0.f};
	
	Vec3 vec31_result = { 1.f, 0.f, 0.f};
	
	#ifdef debug
		printf("before rot x: "); vec3_print(&vec31);
	#endif
	mat_vec_mul_3(rotx_mat, &vec31);
	#ifdef debug
		printf("rot x: "); vec3_print(&vec31);
	#endif
	assert(vec3_equals(&vec31, &vec31_result));

	#ifdef debug
		printf("before rot y: "); vec3_print(&vec32);
	#endif
	mat_vec_mul_3(roty_mat, &vec32);
	#ifdef debug
		printf("rot y: "); vec3_print(&vec32);
	#endif
	assert(vec32.z == -1.f);
	
	#ifdef debug
		printf("before rot z: "); vec3_print(&vec33);
	#endif
	mat_vec_mul_3(rotz_mat, &vec33);
	#ifdef debug
		printf("rot z: "); vec3_print(&vec33);
	#endif
	assert(vec33.y == 1.f);
	
	free(rotx_mat);
	free(roty_mat);
	free(rotz_mat);
	
	#if 0
		//test random numbers
	#endif
	
	float random = rand_path_deg(32);
	assert(random >= -32.f && random <=32.f);
	random = rand_path_deg(22);
	assert(random >= -22.f && random <=22.f);
	random = rand_path_deg(12);
	assert(random >= -12.f && random <=12.f);
	
	random = rand_path_deg(2);
	assert(random >= -2.f && random <=2.f);
	random = rand_path_deg(32);
	assert(random >= -32.f && random <=32.f);
	random = rand_path_deg(32);
	assert(random >= -32.f && random <=32.f);
	random = rand_path_deg(32);
	assert(random >= -32.f && random <=32.f);
	
	
	#if 0
		//test is inside mandelbrotset
	#endif
	
	MandelbrotPoint result;
	int iteratrions = 20;
	float _Complex cp = -2.f+1.f*I;
	
	inside_mandelbrot_set(&cp, iteratrions, &result);
	assert(!result.isin);
	
	cp = 0.3f + 0.3f*I;
	inside_mandelbrot_set(&cp, iteratrions, &result);
	assert(result.isin);
	
	#if 0
		//test linear interpolation
	#endif
	
	float intres = interpolate_lin(0.f, -1.f, 0.f, 1.f, 255.f);
	assert(intres == 127.5f);
	
	intres = interpolate_lin(1.f, -1.f, 0.f, 1.f, 255.f);
	assert(intres == 255.f);
	intres = interpolate_lin(-1.f, -1.f, 0.f, 1.f, 255.f);
	assert(intres == 0.f);
	
	#endif

	#ifdef debug
		printf("line intersection denominator:\n");
	#endif
	Vec2 p1 = {-1.f, 1.f};
	Vec2 p2 = {-1.f, -1.f};
	Vec2 p3 = {1.f, 1.f};
	Vec2 p4 = {1.f, -1.f};

	float denominator = line_intersect_denominator(&p1, &p2, &p3, &p4);
	#ifdef debug
		printf("calc denom: %f\n", denominator);
	#endif
	assert(denominator == 0.f);
	assert(lines_intersect(&p1, &p2, &p3, &p4) == false);

	p1 = (Vec2){-1.f, 1.f};
	p2 = (Vec2){-1.f, -1.f};
	p3 = (Vec2){-.9f, 1.f};
	p4 = (Vec2){-.9f, -1.f};

	denominator = line_intersect_denominator(&p1, &p2, &p3, &p4);
	#ifdef debug
		printf("calc denom: %f\n", denominator);
	#endif
	assert(denominator == 0.f);
	assert(lines_intersect(&p1, &p2, &p3, &p4) == false);

	p1 = (Vec2){-1.f, 1.f};
	p2 = (Vec2){1.f, -1.f};
	p3 = (Vec2){-1.f, -1.f};
	p4 = (Vec2){1.f, 1.f};

	denominator = line_intersect_denominator(&p1, &p2, &p3, &p4);
	#ifdef debug
		printf("calc denom: %f\n", denominator);
	#endif
	assert(denominator != 0.f);
	assert(lines_intersect(&p1, &p2, &p3, &p4) == true);

	p3 = (Vec2){-1.f, 1.f};
	p4 = (Vec2){1.f, -1.f};
	p2 = (Vec2){-1.f, -1.f};
	p1 = (Vec2){1.f, 1.f};

	denominator = line_intersect_denominator(&p1, &p2, &p3, &p4);
	#ifdef debug
		printf("calc denom: %f\n", denominator);
	#endif
	assert(denominator != 0.f);

	assert(lines_intersect(&p1, &p2, &p3, &p4) == true);


	p1 = (Vec2){.6f, 1.1f};
	p2 = (Vec2){.4f, .6f};
	p3 = (Vec2){0.f, .0f};
	p4 = (Vec2){.3f, .8f};
	Vec2 intersection = {-100.f, -100.f};

	assert(lineseg_intersect_pt(&intersection, &p1, &p2, &p3, &p4) == false);
	#ifdef debug
		printf("NO INTERSECTION\n");
		vec2_print(&intersection);
	#endif
	
	p1 = (Vec2){-1.f, 1.f};
	p2 = (Vec2){1.f, -1.f};
	p3 = (Vec2){-1.f, -1.f};
	p4 = (Vec2){1.f, 1.f};
	intersection = (Vec2){-100.f, -100.f};

	assert(lines_intersect_pt(&intersection, &p1, &p2, &p3, &p4) == true);
	#ifdef debug
		printf("intersection at 0 / 0:\n");
		vec2_print(&intersection);
	#endif
	assert(intersection.x == 0.f);
	assert(intersection.y == 0.f);

	assert(lineseg_intersect_pt(&intersection, &p1, &p2, &p3, &p4) == true);
	#ifdef debug
		printf("line seg intersection at 0 / 0:\n");
		vec2_print(&intersection);
	#endif
	assert(intersection.x == 0.f);
	assert(intersection.y == 0.f);

	p1 = (Vec2){-1.5f, .5f};
	p2 = (Vec2){.5f, -1.5f};
	p3 = (Vec2){-1.5f, -1.5f};
	p4 = (Vec2){.5f, .5f};
	intersection = (Vec2){-100.f, -100.f};

	assert(lines_intersect_pt(&intersection, &p1, &p2, &p3, &p4) == true);
	#ifdef debug
		printf("intersection at -0.5 / -0.5:\n");
		vec2_print(&intersection);
	#endif
	assert(intersection.x == -0.5f);
	assert(intersection.y == -0.5f);

	assert(lineseg_intersect_pt(&intersection, &p1, &p2, &p3, &p4) == true);
	#ifdef debug
		printf("line seg intersection at -0.5 / -0.5:\n");
		vec2_print(&intersection);
	#endif
	assert(intersection.x == -0.5f);
	assert(intersection.y == -0.5f);

	p1 = (Vec2){-.5f, 1.5f};
	p2 = (Vec2){2.f, .5f};
	p3 = (Vec2){1.f, -.5f};
	p4 = (Vec2){1.f, 2.f};
	intersection = (Vec2){-100.f, -100.f};

	assert(lines_intersect_pt(&intersection, &p1, &p2, &p3, &p4) == true);
	#ifdef debug
		printf("intersection at 1 / 0.9:\n");
		vec2_print(&intersection);
	#endif
	assert(intersection.x == 1.f);
	assert(intersection.y == 0.9f);

	assert(lineseg_intersect_pt(&intersection, &p1, &p2, &p3, &p4) == true);
	#ifdef debug
		printf("line seg intersection at 1 / 0.9:\n");
		vec2_print(&intersection);
	#endif
	assert(intersection.x == 1.f);
	assert(intersection.y == 0.9f);

	point = (Vec3){0.5f, 1.f, 0.5f};
	Vec3 plane_p1 = {0.f, 0.f, 0.f};
	Vec3 plane_p2 = {0.f, 0.f, 1.f};
	Vec3 plane_p3 = {1.f, 0.f, 0.f};
	float distance = mu_point_plane_distance(&point, &plane_p1, &plane_p2, &plane_p3);
	assert(distance == 1.f);

	point = (Vec3){0.5f, 0.5f, 0.5f};
	Vec3 sub1;
	Vec3 sub2;
	Vec3 _norm;
	vec3_sub_dest(&sub1, &plane_p2, &plane_p1);
	vec3_sub_dest(&sub2, &plane_p3, &plane_p1);

	vec3_cross_dest(&_norm, &sub1, &sub2); 

	distance = mu_point_plane_distance_normal(&point, &plane_p1,&_norm);
	assert(distance == 0.5f);

	point = (Vec3){0.5f, -0.5f, 0.5f};

	distance = mu_point_plane_distance_normal(&point, &plane_p1,&_norm);
	assert(distance == -0.5f);

	//bool mu_line_plane_intersection(Vec3 *_intersect, Vec3 * _line_p1, Vec3 * _line_p2, Vec3 * _plane_p1, Vec3 * _plane_p2, Vec3 * _plane_p3)
	Vec3 inter_pt;
	Vec3 line_p1 = {0.5f, 0.5f, 0.5f};
	Vec3 line_p2 = {0.5f, -0.5f, 0.5f};
	bool intersects = mu_line_plane_intersection(&inter_pt, &line_p1, &line_p2, &plane_p1, &plane_p2, &plane_p3);

	assert(intersects == true);
	Vec3 expected_intersection = {0.5f, 0.f, 0.5f};
	assert(vec3_equals(&inter_pt, &expected_intersection));

	line_p1 = (Vec3){0.5f, 0.5f, 0.5f};
	line_p2 = (Vec3){-0.5f, 0.5f, -0.5f};
	intersects = mu_line_plane_intersection(&inter_pt, &line_p1, &line_p2, &plane_p1, &plane_p2, &plane_p3);

	assert(intersects == false);

	line_p1 = (Vec3){0.5f, 0.5f, 0.5f};
	line_p2 = (Vec3){-0.5f, -0.5f, -0.5f};
	intersects = mu_line_plane_intersection(&inter_pt, &line_p1, &line_p2, &plane_p1, &plane_p2, &plane_p3);

	assert(intersects == true);
	expected_intersection = (Vec3){0.f, 0.f, 0.0f};
	assert(vec3_equals(&inter_pt, &expected_intersection));


	Vec3 p1__ = {-1.f, -1.f, 0.f};
	Vec3 p2__ = {-1.f, 1.f, 0.f};
	Vec3 p3__ = {1.f, -1.f, 0.f};
	Vec3 p21;
	Vec3 p31;
	Vec3 n__;
	vec3_sub_dest(&p21, &p2__, &p1__);
	vec3_sub_dest(&p31, &p3__, &p1__);

	vec3_cross_dest(&n__, &p21, &p31);
	#ifdef debug 
		printf("p21 X p31:"); 
		vec3_print(&n__); 
		printf("p21 X p31 (normalized):");
	#endif
	vec3_normalize(&n__);
	#ifdef debug 
	vec3_print(&n__);
	#endif
	vec3_cross_dest(&n__, &p31, &p21);
	#ifdef debug 
	printf("p31 X p21:");
	vec3_print(&n__);
	printf("p31 X p21 (normalized):");
	#endif
	vec3_normalize(&n__);
	#ifdef debug
	vec3_print(&n__);
	#endif

	Vec2 points[5] = {{7.f, 1.f}, {8.f, 5.f}, {5.f, 4.f}, {2.f, 5.f}, {1.f, 1.f}};

	float polyarea = polygon_area_2D(&points[0], 5);
	assert(polyarea == 21.f);
	assert(polygon_2D_is_clockwise(&points[0], 5) == false);

	Vec2 points2[5] = { {1.f, 1.f}, {2.f, 5.f}, {5.f, 4.f}, {8.f, 5.f}, {7.f, 1.f}};

	polyarea = polygon_area_2D(&points2[0], 5);
	assert(polyarea == -21.f);
	assert(polygon_2D_is_clockwise(&points2[0], 5) == true);

	#ifdef debug
		printf("End testing math utils:\n");
	#endif
	
	return 0;
}