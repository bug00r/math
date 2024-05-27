#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "dl_list.h"
#include "utilsmath.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef debug
#include <stdio.h>
#endif

typedef void (*RASTER_FUNC_2D)(int32_t const * const x, int32_t const * const y, void *data);
typedef void (*RASTER_BEZIER_FUNC_2D)(Vec2 const * const p1, Vec2 const * const p2, void *data);

Vec2** geometry_convex_hull(Vec2 *points, size_t cnt_points);

void geometry_line(Vec2 *start, Vec2 *end, RASTER_FUNC_2D rFunc, void *data);

void geometry_circle(Vec2 *center, int32_t *radius, RASTER_FUNC_2D rFunc, void *data);

void geometry_ellipse(Vec2 *center, int32_t *_a, int32_t *_b, RASTER_FUNC_2D rFunc, void *data);

/**
 * functions goes throught vec3 array and will calculate triangles in an simple way.
 * the list are containing vec3 instances for triangles. Every 3 vecs a trinagle ends
 * as sequence of t1p1,t1p2,t1p3,t2p1,t2p2,t2p3,...  
 *      t1 = triangle 1
 *      t2 = triangle 2
 *      t1p1 = triangle 1 point 1 ....
 */
DlList *  geometry_triangulate(const Vec3 *vecs, size_t cnt_vecs);

void geometry_bezier1(Vec2 *start, Vec2 *cp, Vec2 *end, uint32_t *steps, RASTER_BEZIER_FUNC_2D rFunc, void *data);
void geometry_bezier2(Vec2 *start, Vec2 *cp1, Vec2 *cp2, Vec2 *end, uint32_t *steps, RASTER_BEZIER_FUNC_2D rFunc, void *data);

#endif