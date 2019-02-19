void 
create_diamond_square(diamond_square_t * param){
	noise_t * noise = param->noise;
	int length = param->length;
	float startseed = param->startseed;
	float seed = param->seed;
	float reduction = param->reduction;
	float (*middlefunc)(float x1, float x2, float x3, float x4) = param->middlefunc;
	float (*seedreducefunc)(const float seed, const float reduction) = param->seedreducefunc;
	
	float * noise_array = (float *)noise->map->entries;
	int noise_width = noise->map->config->size;
	int maxidx = noise_width - 1;
	int usedwidth = maxidx;
	maxidx *= maxidx;
	int cntsquare = (noise_width - 1) / length;
	int middle = length >> 1;
	#ifdef debug
		printf("oldmiddle: %i, newmiddle: %i ,squares: %i\n", length, middle, cntsquare);
	#endif	
	float colval;
	if (cntsquare == 1){
		getnewcolor(noise, &startseed, &noise_array[0]);
		getnewcolor(noise, &startseed, &noise_array[length]);
		getnewcolor(noise, &startseed, &noise_array[length*length+length]);
		getnewcolor(noise, &startseed, &noise_array[length*length + (2*length)]);
	}
	#if 0
		//create all new middle points
	#endif
	for (int sqy = 0; sqy < cntsquare; ++sqy){
		int sqx = 0;
		for (; sqx < cntsquare; ++sqx){
			//for each square
			int lt = sqy * length * noise_width + (sqx*length);
			int rt = sqy * length * noise_width + ((sqx+1)*length);
			int lb = (sqy+1) * length * noise_width + (sqx*length);
			int rb = (sqy+1) * length * noise_width + ((sqx+1)*length);
			//middlepoint
			int x = (sqx*length) + middle;
			int y = (sqy*length) + middle;
			#if defined(debug) && debug == 2
				printf("sqx: %i, sqy: %i, x: %i, y: %i \n", sqx, sqy, x, y);
				printf("middelpoint: x: %i, y: %i \n", x, y);
			#endif
			//array_get_ref(noise_array,lt)
			colval = (noise_array[lt] + noise_array[rt] + noise_array[lb] + noise_array[rb])*0.25;
			colval += seedrndlh(-seed, seed);		
			noise->min = fminf(noise->min, colval);
			noise->max = fmaxf(noise->max, colval);
			noise_array[y * noise_width + x] = colval;
		}
	}	
	#if 0
		//create all new sidepoints
	#endif
	for (int sqy = 0; sqy < cntsquare; ++sqy){
		int sqx = 0;
		for (; sqx < cntsquare; ++sqx){
			//for each square			
			float lt_val = noise_array[sqy * length * noise_width + (sqx*length)];
			float rt_val = noise_array[sqy * length * noise_width + ((sqx+1)*length)];
			float lb_val = noise_array[(sqy+1) * length * noise_width + (sqx*length)];
			float rb_val = noise_array[(sqy+1) * length * noise_width + ((sqx+1)*length)];
			
			//middlepoint
			int x = (sqx*length) + middle;
			int y = (sqy*length) + middle;
			
			float middleidx_val = noise_array[y * noise_width + x];
			//sidepoints
			//up
			int y2 = y - length;
			if ( y2 < 0 ) { 
				y2 += usedwidth; 
			} 
			
			colval = (*middlefunc)(lt_val, rt_val, middleidx_val, noise_array[y2 * noise_width + x]);
			colval += seedrndlh(-seed, seed);
			noise->min = fminf(noise->min, colval);
			noise->max = fmaxf(noise->max, colval);
			y2 = y - middle;
			noise_array[y2 * noise_width + x] = colval;
			
			//down
			y2 = y + length;
			if (  y2 > usedwidth ) { 
				y2 -= usedwidth;
			}
			
			colval = (*middlefunc)(lb_val, rb_val, middleidx_val, noise_array[ y2 * noise_width + x]);
			colval += seedrndlh(-seed, seed);
			noise->min = fminf(noise->min, colval);
			noise->max = fmaxf(noise->max, colval);
			y2 = y + middle;
			noise_array[y2 * noise_width + x] = colval;

			//left
			int x2 = x - length;
			if (  x2 < 0 ) { 
				x2 += usedwidth;
			}
			
			colval = (*middlefunc)(lt_val, lb_val, middleidx_val, noise_array[y * noise_width + x2]);
			colval += seedrndlh(-seed, seed);
			noise->min = fminf(noise->min, colval);
			noise->max = fmaxf(noise->max, colval);
			x2 = x - middle;
			noise_array[y * noise_width + x2] = colval;

			//right
			x2 = x + length;
			if (  x2 > usedwidth ) {
				x2 -= usedwidth;
			}
			
			colval = (*middlefunc)(rt_val, rb_val, middleidx_val , noise_array[y * noise_width + x2]);
			colval += seedrndlh(-seed, seed);
			noise->min = fminf(noise->min, colval);
			noise->max = fmaxf(noise->max, colval);
			x2 = x + middle;
			noise_array[y * noise_width + x2] = colval;
		}
	}	
	if(middle >= 2){
		//OLD Version should set as seed reduction func param->seed = seed-reduction;
		//param->seed = seed * reduction;
		param->seed = seedreducefunc(seed, reduction);
		param->length = middle;
		create_diamond_square(param);
	}
}