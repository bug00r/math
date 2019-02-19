static void create_evolution_steps(evolution_t * param, evolution_item_t * ev_items) {
		
		unsigned int spawnable_item_max = param->cnt_items;
		noise_t * noise = param->noise;
		int _w = noise->map->config->cnt;
		int _h = noise->map->config->size;
		
		float fref;
		array_error_t array_res;
		
		for (unsigned int h = _h; h--;){
		  for (unsigned int w = _w; w--;){
				array_res = farray2D_get(noise->map, w, h, &fref);
				if(array_res==ARRAY_ERR_OK){
					float min_value = FLT_MAX;
					unsigned int cnt_min = 0;
					evolution_item_t * f_ev_item = NULL;
					for (unsigned int hi = spawnable_item_max; hi--;){
						f_ev_item = &ev_items[hi];
						float dx = w - f_ev_item->width;
						float dy = h - f_ev_item->height;
						float cur_len = sqrtf((dx*dx) + (dy*dy));
						if ( cur_len < min_value ) {
							min_value = cur_len;
							cnt_min = 1;
						} else if ( cur_len == min_value ) {
							++cnt_min;
						}
					}
					if (cnt_min > 1 ) {
						farray2D_set(noise->map, w, h, 0.f);
					} else if ((f_ev_item->width == w) && (f_ev_item->height == h)) { 
						farray2D_set(noise->map, f_ev_item->width, f_ev_item->height, 1.f);
					} else {
						farray2D_set(noise->map, w, h, 0.25f);
					}
					
					
					//float cur_len = sqrtf((x*x) + (y*y));
				}
			}
		}
}

void create_evolution(evolution_t * param) {
	noise_t * noise = param->noise;
	int _w = noise->map->config->cnt;
	int _h = noise->map->config->size;
	noise->min = 0.f;
	noise->max = 1.f;
	param->cnt_items = (unsigned int)seedrndlh(20.f, 100.f);
	evolution_item_t * ev_items = malloc(param->cnt_items * sizeof(evolution_item_t));
	
	for (unsigned int cur_item = param->cnt_items; cur_item--;) {
		int new_w = (int)fabsf(seedrndlh(-_w, _w));
		int new_h = (int)fabsf(seedrndlh(-_h, _h));
		printf("new point %i: %i %i", cur_item, new_w, new_h);
		evolution_item_t * cur_ev_item = &ev_items[cur_item];
		cur_ev_item->width = new_w;
		cur_ev_item->height = new_h;
	}
	
	create_evolution_steps(param, ev_items);

	free(ev_items);
}
