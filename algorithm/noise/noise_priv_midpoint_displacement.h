typedef struct {
	noise_t * noise;
	int length; 
	float startseed, seed, reduction;
	float (*middlefunc)(const float x1, const float x2, const float x3, const float x4);
	float (*middlefunc2)(const float x1, const float x2);
	float (*seedreducefunc)(const float seed, const float reduction);
} midpoint_displacement_t;

void create_midpoint_displacement( midpoint_displacement_t * param );
