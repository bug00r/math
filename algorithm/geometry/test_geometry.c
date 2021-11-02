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

#ifdef debug
static void
__geometry_vec3_print_wrapper(vec3_t **vec) 
{
    printf("%p = ",*vec);vec3_print(*vec);
}
#endif

static void test_geometry_triangulation() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	vec3_t points[8] = { {5.f, .0f, .0f} , { 5.f, 10.f, .0f}, { .0f, 10.f, .0f}  , { .0f, 14.f, .0f}, 
						  {14.f, 14.f, .0f}, { 14.f, 10.f, .0f}, { 9.f, 10.f, .0f}, { 9.f, .0f, .0f}};

	#ifdef debug
    	for (size_t curSrcPt = 0; curSrcPt < 8 ; ++curSrcPt) {
			printf("[%u]: %p = ", curSrcPt, &points[curSrcPt]);vec3_print(&points[curSrcPt]);
		}
    #endif


	dl_list_t * triangles = geometry_triangulate(points, 8);

	#ifdef debug
		printf("LETTER T\n");
    	dl_list_each(triangles, (EACH_FUNC)__geometry_vec3_print_wrapper);
    #endif

	dl_list_clear(triangles);
	dl_list_free(&triangles);

	DEBUG_LOG("<<<\n");
}

static void test_geometry_triangulation_mc() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	vec3_t points2[14] = { {0.f, .0f, .0f} , { .0f, .8f, .0f}, { .2f, 1.1f, .0f}  , { .3f, 1.4f, .0f}, 
						 {.5f, 1.1f, .0f}, { .8f, 0.9f, .0f}, { 1.f, 1.2f, .0f}, { 1.0f, 0.7f, .0f},
						 { 0.7f, 0.6f, .0f}, { 1.0f, 0.4f, .0f}, { 0.7f, .0f, .0f}, { .5f, .2f, .0f},
						 { .3f, .0f, .0f}, { 0.2f, 0.2f, .0f}};


	dl_list_t * triangles = geometry_triangulate(points2, 14);

	#ifdef debug
		printf("FIRST MORE COMPLEX\n");
    	dl_list_each(triangles, (EACH_FUNC)__geometry_vec3_print_wrapper);
    #endif

	dl_list_clear(triangles);
	dl_list_free(&triangles);

	DEBUG_LOG("<<<\n");
}

static void test_geometry_triangulation_vc() {
	DEBUG_LOG_ARGS(">>> %s => %s\n", __FILE__, __func__);

	vec3_t points3[10] = { {0.f, .0f, .0f} , { .0f, 1.1f, .0f}, { .3f, .8f, .0f}  , { .6f, 1.1f, .0f}, 
						 {.4f, .6f, .0f}, { .1f, 0.9f, .0f}, { .1f, .3f, .0f}, { .4f, .5f, .0f},
						 { 0.6f, 0.1f, .0f}, { .3f, 0.3f, .0f}};

	dl_list_t * triangles = geometry_triangulate(points3, 10);

	#ifdef debug
		printf("SECOND VERY COMPLEX\n");
    	dl_list_each(triangles, (EACH_FUNC)__geometry_vec3_print_wrapper);
    #endif

	dl_list_clear(triangles);
	dl_list_free(&triangles);

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

	//test_geometry_triangulation();

	//test_geometry_triangulation_mc();

	test_geometry_triangulation_vc();

	DEBUG_LOG("<< end geometry tests:\n");

	return 0;
}