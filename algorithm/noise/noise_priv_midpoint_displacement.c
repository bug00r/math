void 
create_midpoint_displacement( midpoint_displacement_t * param ){
	noise_t * noise = param->noise;
	int length = param->length;
	float startseed = param->startseed;
	float seed = param->seed;
	float reduction = param->reduction;
	float (*middlefunc)(float x1, float x2, float x3, float x4) = param->middlefunc;
	float (*middlefunc2)(float x1, float x2) = param->middlefunc2;
	float (*seedreducefunc)(const float seed, const float reduction) = param->seedreducefunc;
	
	float * noise_array = (float *)noise->map->entries;
	int noise_width = noise->map->config->size;
	int cntsquare = (noise_width - 1) / length;
	int middle = length >> 1;
	float colval;
	#ifdef debug
		printf("oldmiddle: %i, newmiddle: %i ,squares: %i\n", length, middle, cntsquare);
	#endif
	
	if (cntsquare == 1){
		getnewcolor(noise, &startseed, &noise_array[0]);
		getnewcolor(noise, &startseed, &noise_array[length]);
		getnewcolor(noise, &startseed, &noise_array[length*length+length]);
		getnewcolor(noise, &startseed, &noise_array[length*length + (2*length)]);
	}

	for (int sqy = 0; sqy < cntsquare; ++sqy){
		int sqx = 0;
		for (; sqx < cntsquare; ++sqx){
			float lt_val = noise_array[sqy * length * noise_width + (sqx*length)];
			float rt_val = noise_array[sqy * length * noise_width + ((sqx+1)*length)];
			float lb_val = noise_array[(sqy+1) * length * noise_width + (sqx*length)];
			float rb_val = noise_array[(sqy+1) * length * noise_width + ((sqx+1)*length)];
			
			//middlepoint
			int x = (sqx*length) + middle;
			int y = (sqy*length) + middle;
			
			colval = (*middlefunc2)(lt_val, rt_val) + seedrndlh(-seed, seed);
			noise->min = fminf(noise->min, colval);
			noise->max = fmaxf(noise->max, colval);
			noise_array[(y-middle) * noise_width + x] = colval;
			
			colval = (*middlefunc2)(lb_val, rb_val) + seedrndlh(-seed, seed);
			noise->min = fminf(noise->min, colval);
			noise->max = fmaxf(noise->max, colval);
			noise_array[(y+middle) * noise_width + x] = colval;
			
			colval = (*middlefunc2)(lt_val, lb_val) + seedrndlh(-seed, seed);
			noise->min = fminf(noise->min, colval);
			noise->max = fmaxf(noise->max, colval);
			noise_array[y * noise_width + x - middle] = colval;
			
			colval = (*middlefunc2)(rt_val, rb_val) + seedrndlh(-seed, seed);
			noise->min = fminf(noise->min, colval);
			noise->max = fmaxf(noise->max, colval);
			noise_array[y * noise_width + x + middle] = colval;
			
			colval = (*middlefunc)(	noise_array[(y-middle) * noise_width + x],
									noise_array[(y+middle) * noise_width + x],
									noise_array[y * noise_width + x - middle],
									noise_array[y * noise_width + x + middle]);
									
			colval += seedrndlh(-seed, seed);
			noise->min = fminf(noise->min, colval);
			noise->max = fmaxf(noise->max, colval);
			noise_array[y * noise_width + x] = colval;			
		}
	}	
	if(middle >= 2){
		// OLD VErsion param->seed = seed-reduction;
		//param->seed = seed * reduction;
		param->seed = seedreducefunc(seed, reduction);
		param->length = middle;
		create_midpoint_displacement(param);
	}
}