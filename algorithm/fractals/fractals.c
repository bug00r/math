#include "fractals.h"

julia_t * 
julia_new(const unsigned int width, const unsigned int height){
	julia_t * newjulia = malloc(sizeof(julia_t));
	newjulia->map = array2D_new(width, height, sizeof(julia_point_t));
	return newjulia;
}

void 
julia_free(julia_t * julia){
	array_free(julia->map);
	free(julia);
}

mandelbrot_t * 
mandelbrot_new(const unsigned int width, const unsigned int height){
	mandelbrot_t * newmb = malloc(sizeof(mandelbrot_t));
	newmb->map = array2D_new(width, height, sizeof(mandelbrot_point_t));
	return newmb;
}

void mandelbrot_free(mandelbrot_t * mandelbrot){
	array_free(mandelbrot->map);
	free(mandelbrot);
}

void 
create_mandelbrot(const mandelbrot_t * mandelbrot){
	float curreal = mandelbrot->minreal;
	float curimag = mandelbrot->minimag;
	mandelbrot_point_t * mandelbrot_array = (mandelbrot_point_t *)mandelbrot->map->entries;
	float _Complex cp;

	int mwidth = mandelbrot->map->config->size;
	int mheight = mandelbrot->map->config->cnt;
	float currealstep = (mandelbrot->maxreal - mandelbrot->minreal)/mwidth;
	float curimagstep = (mandelbrot->maximag - mandelbrot->minimag)/mheight;
	
	int curw = 0; 
	for( ; curreal < mandelbrot->maxreal ; curreal += currealstep){
		int curh = mheight-1;
		for( ; curimag < mandelbrot->maximag ; curimag += curimagstep, --curh){
			cp = curreal + curimag * I;
			inside_mandelbrot_set(&cp, mandelbrot->cntiterations, &mandelbrot_array[curh * mwidth + curw]);			
		}
		curimag = mandelbrot->minimag;
		++curw;
	}
}

float _Complex julia_pfunc_quad_plus_c(const float _Complex *cp, const float _Complex *c){
	return cpowf(*cp, 2) + *c;
}

float _Complex julia_pfunc_third_plus_c(const float _Complex *cp, const float _Complex *c){
	return cpowf(*cp, 3) + *c;
}

float _Complex julia_pfunc_fourth_plus_c(const float _Complex *cp, const float _Complex *c){
	return cpowf(*cp, 4) + *c;
}

float _Complex julia_pfunc_exp_plus_c(const float _Complex *cp, const float _Complex *c){
	return cexpf(cpowf(*cp, 3)) - *c;
}

float _Complex julia_pfunc_ten_plus_c(const float _Complex *cp, const float _Complex *c){
	return cpowf(*cp, 10) + *c;
}

float _Complex julia_pfunc_quad_plus_c_2(const float _Complex *cp, const float _Complex *c){
	float _Complex pow2_z = cpowf(*cp, 2);
	return (pow2_z + *c) / (pow2_z - *c);
}

float _Complex julia_pfunc_quad_plus_c_1_2(const float _Complex *cp, const float _Complex *c){
	float _Complex pow2_z = cpowf(*cp, 2);
	return (pow2_z - *c) / (pow2_z + *c);
}

float _Complex julia_pfunc_sqrt_plus_c(const float _Complex *cp, const float _Complex *c){
	float _Complex sqrt2_z = csqrtf(*cp);
	return (sqrt2_z + *c);
}

float _Complex julia_pfunc_sqrt_minus_c(const float _Complex *cp, const float _Complex *c){
	float _Complex sqrt2_z = csqrtf(*cp);
	return (sqrt2_z - *c);
}

float _Complex julia_pfunc_quad_plus_c_3(const float _Complex *cp, const float _Complex *c){
	float _Complex pow3_z = cpowf(*cp, 3);
	return (pow3_z + *c) / (pow3_z - *c);
}

float _Complex julia_pfunc_3_2_div_pc(const float _Complex *cp, const float _Complex *c) {
	return ((1.f - (cpowf(*cp, 3)/6.f)) / cpowf(*cp - (cpowf(*cp, 2)/2.f),2)) + *c;
}

float _Complex julia_pfunc_pow_3_p_2_p_1_p_c(const float _Complex *cp, const float _Complex *c) {
	return cpowf(*cp, 3) + cpowf(*cp, 2) + *cp + *c; 
}

float _Complex julia_pfunc_px_random(const float _Complex *cp, const float _Complex *c){
	int fidx = (int)seedrnd(2.f);
	switch(fidx) {
		case 0: return julia_pfunc_quad_plus_c_2(cp, c); break;
		case 1: return julia_pfunc_quad_plus_c_1_2(cp, c); break;
		default: return julia_pfunc_quad_plus_c_2(cp, c);
	}
}

void 
create_julia(const julia_t * julia){
	float curreal = julia->minreal;
	float curimag = julia->minimag;
	julia_point_t * julia_array = (julia_point_t *)julia->map->entries;
	float _Complex cp;

	int jwidth = julia->map->config->size;
	int jheight = julia->map->config->cnt;
	float currealstep = (julia->maxreal - julia->minreal)/jwidth;
	float curimagstep = (julia->maximag - julia->minimag)/jheight;
	
	int curw = 0; 
	for( ; curreal < julia->maxreal ; curreal += currealstep){
		int curh = jheight-1;
		for( ; curimag < julia->maximag ; curimag += curimagstep, --curh){
			cp = curreal + curimag * I;
			inside_julia_set(&cp, &julia->c, julia->cntiterations, &julia_array[curh * jwidth + curw], julia->polyfunc);	
		}
		curimag = julia->minimag;
		++curw;
	}
}