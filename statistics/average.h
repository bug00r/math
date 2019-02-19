#ifndef AVERAGE_H
#define AVERAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils_math.h"

float middle_arithmetic(const float x1, const float x2, const float x3, const float x4);
float middle_arithmetic2(const float x1, const float x2);
float middle_harmonic(const float x1, const float x2, const float x3, const float x4);
float middle_harmonic2(const float x1, const float x2);
float middle_quantil(const float x1, const float x2, const float x3, const float x4);
float middle_median(const float x1, const float x2, const float x3, const float x4);
float middle_quad(const float x1, const float x2, const float x3, const float x4);
float middle_quad2(const float x1, const float x2);
float middle_cubic(const float x1, const float x2, const float x3, const float x4);
float middle_cubic2(const float x1, const float x2);
float middle_geometric(const float x1, const float x2, const float x3, const float x4);
float middle_geometric2(const float x1, const float x2);
float middle_hoelder(const float x1, const float x2, const float x3, const float x14);
float middle_hoelder2(const float x1, const float x2);

#endif