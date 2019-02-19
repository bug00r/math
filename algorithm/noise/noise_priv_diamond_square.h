typedef struct {
	noise_t * noise; 
	int length;
	float startseed, seed, reduction;
	float (*middlefunc)(const float x1, const float x2, const float x3, const float x4);
	float (*seedreducefunc)(const float seed, const float reduction);
} diamond_square_t;

void create_diamond_square(diamond_square_t * param);
