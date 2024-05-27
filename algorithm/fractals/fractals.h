#ifndef FRACTALS_H
#define FRACTALS_H

#include "utilsmath.h"
#include "array.h"

typedef struct {
	float minreal; 
	float maxreal; 
	float minimag;
	float maximag;
	int cntiterations;
	Array * map;
} Mandelbrot;

typedef struct {
	float minreal; 
	float maxreal; 
	float minimag;
	float maximag;
	int cntiterations;
	float _Complex c;
	float _Complex (*polyfunc)(const float _Complex *cp, const float _Complex *c);
	Array * map;
} Julia;

#if 0
	//z^2 + c
#endif
float _Complex julia_pfunc_quad_plus_c(const float _Complex *cp, const float _Complex *c);

#if 0
	//z^3 + c  example : f(z) = z**3 + 0.400
#endif
float _Complex julia_pfunc_third_plus_c(const float _Complex *cp, const float _Complex *c);

#if 0
	//z^4 + c  example : f(z) = z**4 + 0.400
#endif
float _Complex julia_pfunc_fourth_plus_c(const float _Complex *cp, const float _Complex *c);

#if 0
	//z^10 + c  example : f(z) = z**10 + 0.400
#endif
float _Complex julia_pfunc_ten_plus_c(const float _Complex *cp, const float _Complex *c);

#if 0
	//f(z) = exp(z) - 0.65
#endif
float _Complex julia_pfunc_exp_plus_c(const float _Complex *cp, const float _Complex *c);

#if 0
	//z^2 + c / z^2 - c
#endif
float _Complex julia_pfunc_quad_plus_c_2(const float _Complex *cp, const float _Complex *c);

#if 0
	//z^3 + c / z^3 - c
#endif
float _Complex julia_pfunc_quad_plus_c_3(const float _Complex *cp, const float _Complex *c);

#if 0
	//z^2 - c / z^2 + c
#endif
float _Complex julia_pfunc_quad_plus_c_1_2(const float _Complex *cp, const float _Complex *c);
#if 0
	//sqrt(z) + c
#endif
float _Complex julia_pfunc_sqrt_plus_c(const float _Complex *cp, const float _Complex *c);
#if 0
	//sqrt(z) - c
#endif
float _Complex julia_pfunc_sqrt_minus_c(const float _Complex *cp, const float _Complex *c);
#if 0
	//((1-z³/6) / (z - z²/2)) + c
#endif
float _Complex julia_pfunc_3_2_div_pc(const float _Complex *cp, const float _Complex *c);
#if 0
	//i³ + i² + i + c
#endif
float _Complex julia_pfunc_pow_3_p_2_p_1_p_c(const float _Complex *cp, const float _Complex *c);
#if 0
	//randomized of one of above
#endif
float _Complex julia_pfunc_px_random(const float _Complex *cp, const float _Complex *c);


Julia * julia_new(const unsigned int width, const unsigned int height);
void julia_free(Julia * julia);

Mandelbrot * mandelbrot_new(const unsigned int width, const unsigned int height);
void mandelbrot_free(Mandelbrot * mandelbrots);

void create_mandelbrot(const Mandelbrot * mandelbrot);
void create_julia(const Julia * julia);

#endif