#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vec.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef debug
#include <stdio.h>
#endif

typedef void (*RASTER_FUNC_2D)(int32_t const * const x, int32_t const * const y, void *data);

vec2_t** geometry_convex_hull(vec2_t *points, size_t cnt_points);

void geometry_line(vec2_t *start, vec2_t *end, RASTER_FUNC_2D rFunc, void *data);

void geometry_circle(vec2_t *center, int32_t *radius, RASTER_FUNC_2D rFunc, void *data);

void geometry_ellipse(vec2_t *center, int32_t *_a, int32_t *_b, RASTER_FUNC_2D rFunc, void *data);

#endif