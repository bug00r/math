#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vec.h"
#include <stdlib.h>
#include <string.h>

#ifdef debug
#include <stdio.h>
#endif

vec2_t** geometry_convex_hull(vec2_t *points, size_t cnt_points);

#endif