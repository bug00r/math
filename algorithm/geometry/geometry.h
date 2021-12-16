#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "dl_list.h"
#include "utils_math.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef debug
#include <stdio.h>
#endif

typedef void (*RASTER_FUNC_2D)(int32_t const * const x, int32_t const * const y, void *data);
typedef void (*RASTER_BEZIER_FUNC_2D)(vec2_t const * const p1, vec2_t const * const p2, void *data);

vec2_t** geometry_convex_hull(vec2_t *points, size_t cnt_points);

void geometry_line(vec2_t *start, vec2_t *end, RASTER_FUNC_2D rFunc, void *data);

void geometry_circle(vec2_t *center, int32_t *radius, RASTER_FUNC_2D rFunc, void *data);

void geometry_ellipse(vec2_t *center, int32_t *_a, int32_t *_b, RASTER_FUNC_2D rFunc, void *data);

/**
 * functions goes throught vec3 array and will calculate triangles in an simple way.
 * the list are containing vec3 instances for triangles. Every 3 vecs a trinagle ends
 * as sequence of t1p1,t1p2,t1p3,t2p1,t2p2,t2p3,...  
 *      t1 = triangle 1
 *      t2 = triangle 2
 *      t1p1 = triangle 1 point 1 ....
 */
dl_list_t *  geometry_triangulate(const vec3_t *vecs, size_t cnt_vecs);

void geometry_bezier1(vec2_t *start, vec2_t *cp, vec2_t *end, uint32_t *steps, RASTER_BEZIER_FUNC_2D rFunc, void *data);
void geometry_bezier2(vec2_t *start, vec2_t *cp1, vec2_t *cp2, vec2_t *end, uint32_t *steps, RASTER_BEZIER_FUNC_2D rFunc, void *data);

#endif