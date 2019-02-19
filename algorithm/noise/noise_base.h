typedef struct {
	array_t * map;
	float min, max;
} noise_t;

noise_t * noise_new(const unsigned int width, const unsigned int height);
void noise_free(noise_t * noise);

float create_noise_value(noise_t * noise,  const float range_min, const float range_max);
void getnewcolor(noise_t * noise,  const float * startseed, float * colortarget);

float seed_reduction_add(const float seed, const float reduction);
float seed_reduction_sub(const float seed, const float reduction);
float seed_reduction_mul(const float seed, const float reduction);
float seed_reduction_div(const float seed, const float reduction);
float seed_reduction_add_sqrt(const float seed, const float reduction);
float seed_reduction_sub_sqrt(const float seed, const float reduction);
float seed_reduction_mul_sqrt(const float seed, const float reduction);
float seed_reduction_div_sqrt(const float seed, const float reduction);
float seed_reduction_pow2_p_r_div_pow2_m_r(const float seed, const float reduction);
float seed_reduction_pow2_m_r_div_pow2_p_r(const float seed, const float reduction);
float seed_reduction_arithmetic_add(const float seed, const float reduction);
float seed_reduction_arithmetic_sub(const float seed, const float reduction);
float seed_reduction_arithmetic_mul(const float seed, const float reduction);
float seed_reduction_arithmetic_div(const float seed, const float reduction);
float seed_reduction_hoelder_add(const float seed, const float reduction);
float seed_reduction_hoelder_sub(const float seed, const float reduction);
float seed_reduction_hoelder_mul(const float seed, const float reduction);
float seed_reduction_hoelder_div(const float seed, const float reduction);
float seed_reduction_geometric_add(const float seed, const float reduction);
float seed_reduction_geometric_sub(const float seed, const float reduction);
float seed_reduction_geometric_mul(const float seed, const float reduction);
float seed_reduction_geometric_div(const float seed, const float reduction);
float seed_reduction_cubic_add(const float seed, const float reduction);
float seed_reduction_cubic_sub(const float seed, const float reduction);
float seed_reduction_cubic_mul(const float seed, const float reduction);
float seed_reduction_cubic_div(const float seed, const float reduction);
float seed_reduction_quad_add(const float seed, const float reduction);
float seed_reduction_quad_sub(const float seed, const float reduction);
float seed_reduction_quad_mul(const float seed, const float reduction);
float seed_reduction_quad_div(const float seed, const float reduction);
float seed_reduction_harmonic_add(const float seed, const float reduction);
float seed_reduction_harmonic_sub(const float seed, const float reduction);
float seed_reduction_harmonic_mul(const float seed, const float reduction);
float seed_reduction_harmonic_div(const float seed, const float reduction);

void filter_noise_gauss(noise_t *noise, float deviation);
void filter_noise_circle(noise_t *noise, float radius);
