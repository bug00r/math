#if 0
/**
	This is a Test programm for the noise lib
*/
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "noise.h"

int 
main() 
{
	#ifdef debug
		printf("Start testing noise lib:\n");
	#endif
	

	int w = 17;
	int h = w;
	srand(time(NULL));
	float maxreduction = 2.05f;
	float reduction = maxreduction/((w-1)*(w-1));
	
	Noise * noise = noise_new(w, h);
	#ifdef debug
		printf("noise w: %i, h: %i\n", noise->map->config->cnt, noise->map->config->size);
	#endif
	
	MidpointDisplacement md_param;
	md_param.noise = noise;
	md_param.length = w-1;
	md_param.startseed = 1.f;
	md_param.seed = maxreduction;
	md_param.reduction = reduction;
	md_param.middlefunc = middle_arithmetic;
	md_param.middlefunc2 = middle_arithmetic2;
	md_param.seedreducefunc = seed_reduction_mul;
	create_midpoint_displacement(&md_param);
	
	ArrayIterator * it = array_iterator_new(noise->map);
	
	#ifdef debug
		printf("midpoint array contains[");
		while(array_iterator_has_next(it))
		{
			float * curvalue = (float *)array_iterator_next(it);
			printf(" %f", *curvalue);
		}
		printf("]\n");
	#endif
	
	array_iterator_free(it);
	
	DiamondSquare ds_param;
	ds_param.noise = noise;
	ds_param.length = w-1;
	ds_param.startseed = 1.f;
	ds_param.seed = maxreduction;
	ds_param.reduction = reduction;
	ds_param.middlefunc = middle_arithmetic;
	ds_param.seedreducefunc = seed_reduction_mul;
	create_diamond_square(&ds_param);
	
	it = array_iterator_new(noise->map);
	
	#ifdef debug
		printf("diamond array contains[\n");
		while(array_iterator_has_next(it))
		{
			float * curvalue = (float *)array_iterator_next(it);
			printf(" %f", *curvalue);
			if (it->index % w == 0) printf("\n");
		}
		printf("]\n");
	#endif
	array_iterator_free(it);
	
	filter_noise_gauss(noise, 2.f);
	
	it = array_iterator_new(noise->map);
	
	#ifdef debug
		printf("AFTER FILTER:\ndiamond array contains[\n");
		while(array_iterator_has_next(it))
		{
			float * curvalue = (float *)array_iterator_next(it);
			printf(" %f", *curvalue);
			if (it->index % w == 0) printf("\n");
		}
		printf("]\n");
	#endif
	array_iterator_free(it);
	
	noise_free(noise);
	
	noise = noise_new(w, h);
	
	Evolution ev_param;
	ev_param.noise = noise;
	ev_param.min_value=-1.f;
	ev_param.max_value=2.f;
	ev_param.cnt_items=0;
	ev_param.max_evolution=4;
	create_evolution(&ev_param);
	
	
	it = array_iterator_new(noise->map);
	
	#ifdef debug
		printf("evolution array contains[\n");
		while(array_iterator_has_next(it))
		{
			float * curvalue = (float *)array_iterator_next(it);
			printf(" %f", *curvalue);
			if (it->index % w == 0) printf("\n");
		}
		printf("]\n");
	#endif
	array_iterator_free(it);
	
	noise_free(noise);
	
	#ifdef debug
		printf("End testing noise lib:\n");
	#endif
	
	return 0;
}
