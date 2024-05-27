#if 0
/**
	This is a Test programm for the fractals lib
*/
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "fractals.h"

int 
main() {
	#ifdef debug
		printf("Start testing fractals lib:\n");
	#endif
	
	int w = 512;
	int h = 512;
	
	Julia *julia = julia_new(w, h);
	julia->minreal =  0.f;//-1.3f;
	julia->maxreal =  .5f;//-1.f;
	julia->minimag =  0.f;//-.3f;
	julia->maximag =  .3f;//0.f;
	julia->cntiterations = 200;
	//julia->c = -0.8f + 0.2f*I;
	//julia->c = -1.f + 0.f*I;
	julia->c = -0.f + 1.f*I;
	julia->polyfunc = julia_pfunc_quad_plus_c;
	
	create_julia(julia);
	julia_free(julia);
		
	Mandelbrot *mb = mandelbrot_new(w, h);
	mb->minreal = -2.f;//-1.3f;
	mb->maxreal = 0.5f;//-1.f;
	mb->minimag = -1.f;//-.3f;
	mb->maximag = 1.f;//0.f;
	mb->cntiterations = 20;
	create_mandelbrot(mb);
	mandelbrot_free(mb);
	
	#ifdef debug
		printf("End testing fractals lib:\n");
	#endif
	
	return 0;
}