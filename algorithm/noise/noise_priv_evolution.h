typedef enum {
	SPAWN_BOX, SPAWN_CROSS, SPAWN_DIAG_CROSS
} spawn_type_t;

typedef struct {
	float value;		 			//current value
	float max_value;	 			//max possible value
	float growing_factor;		 	//highest growing amount
	unsigned int level_left;  		//rest of evolution level
	unsigned int max_level; 		//max possible evolution level
	unsigned int spawn;				//spawned n times
	unsigned int max_spawn;			//max spawn count
	unsigned int spawn_range;		//range in x and y which must be checked during every evolution
	spawn_type_t spawn_type;
	unsigned int width;
	unsigned int height;
} evolution_item_t;

typedef struct {
	noise_t * noise;
	float min_value;
	float max_value;
	unsigned int max_evolution;
	unsigned int cnt_items;
} evolution_t;

void create_evolution(evolution_t * param);
