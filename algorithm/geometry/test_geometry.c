#include "geometry.h"

#include "debug.h"

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

static void test_geometry_convex_hull_null() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	vec2_t *points = NULL;
	vec2_t **hull_pts = geometry_convex_hull(points, 5);

	assert(hull_pts == NULL);

	DEBUG_LOG("<<<\n");
}

static void test_geometry_convex_hull() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	vec2_t points[12] = { {1.f, 1.f} , { 2.5f, 2.f}, { 4.f, 1.f}  , { 4.f, 3.f}, 
						 {4.5f,1.5f}, { 3.f, 3.5f}, { 3.5f, 2.f}, { 2.f, 3.f},
						 {1.5f,4.f}, { 1.5f, 2.f}, { 3.f, 0.5f}, { 2.0f, .5f}};
	vec2_t **hull_pts = geometry_convex_hull(points, 12);

	assert(hull_pts != NULL);
	assert(*hull_pts != NULL);

	#ifdef debug
	printf("complete hull: %p\n", hull_pts);
	for ( uint32_t i = 0; hull_pts && hull_pts[i]; ++i ) {
		printf("%p = ",hull_pts[i]);vec2_print(hull_pts[i]);
	}
	#endif

	free(hull_pts);

	DEBUG_LOG("<<<\n");
}

void print_raster(int32_t const * const x, int32_t const * const y, void *data) {
	printf("x/y = %i/%i\n", *x, *y);
}

static void test_geometry_line() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	vec2_t start = { 1,3 };
	vec2_t end = { 12, 9 };
 
	void * data = NULL;

	geometry_line(&start, &end, print_raster, data);


	DEBUG_LOG("<<<\n");
}

static void test_geometry_circle() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	vec2_t center = { 7,7 };
	int32_t radius = 5;
 
	void * data = NULL;

	geometry_circle(&center, &radius, print_raster, data);


	DEBUG_LOG("<<<\n");
}

static void test_geometry_ellipse() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	vec2_t center = { 25,25 };
	int32_t a = 5;  //halfaxis
	int32_t b = 10;
 
	void * data = NULL;

	geometry_ellipse(&center, &a, &b, print_raster, data);


	DEBUG_LOG("<<<\n");
}

int main(int argc, char **argv) {
	(void)argc; (void)argv;

	DEBUG_LOG(">> Start geometry tests:\n");

    test_geometry_convex_hull_null();

	test_geometry_convex_hull();

	test_geometry_line();

	test_geometry_circle();

	test_geometry_ellipse();

	DEBUG_LOG("<< end geometry tests:\n");

	return 0;
}