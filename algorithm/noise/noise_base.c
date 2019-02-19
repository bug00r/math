noise_t * 
noise_new(const unsigned int width, const unsigned int height){
	noise_t * newnoise = malloc(sizeof(noise_t));
	newnoise->map = farray2D_new(width, height);
	newnoise->min = FLT_MAX;
	newnoise->max = FLT_MIN;
	return newnoise;
}

void 
noise_free(noise_t * noise){
	array_free(noise->map);
	free(noise);
}

float create_noise_value(noise_t * noise,  const float range_min, const float range_max) {
	noise_t *curnoise = noise;
	float noiseval = seedrndlh(range_min, range_max);
	curnoise->min = fminf(curnoise->min, noiseval);
	curnoise->max = fmaxf(curnoise->max, noiseval);
	return noiseval;
}

void getnewcolor(noise_t * noise,  const float * startseed, float * colortarget){
	*colortarget = create_noise_value(noise, -*startseed, *startseed);
}


float seed_reduction_add(const float seed, const float reduction) {
	return seed + reduction;
}
float seed_reduction_sub(const float seed, const float reduction) {
	return seed - reduction;
}
float seed_reduction_mul(const float seed, const float reduction) {
	return seed * reduction;
}
float seed_reduction_div(const float seed, const float reduction) {
	return seed / reduction;
}
float seed_reduction_add_sqrt(const float seed, const float reduction) {
	return seed + sqrtf(reduction);
}
float seed_reduction_sub_sqrt(const float seed, const float reduction) {
	return seed - sqrtf(reduction);
}
float seed_reduction_mul_sqrt(const float seed, const float reduction) {
	return seed * sqrtf(reduction);
}
float seed_reduction_div_sqrt(const float seed, const float reduction) {
	return seed / sqrtf(reduction);
}
float seed_reduction_pow2_p_r_div_pow2_m_r(const float seed, const float reduction) {
	return seed * ((powf(seed,2) + reduction)/(powf(seed,2) - reduction));
}
float seed_reduction_pow2_m_r_div_pow2_p_r(const float seed, const float reduction) {
	return seed * ((powf(seed,2) - reduction)/(powf(seed,2) + reduction));
}
float seed_reduction_arithmetic_add(const float seed, const float reduction) 
{
	return seed + middle_arithmetic2(seed, reduction);
}
float seed_reduction_arithmetic_sub(const float seed, const float reduction) 
{
	return seed - middle_arithmetic2(seed, reduction);
}
float seed_reduction_arithmetic_mul(const float seed, const float reduction) 
{
	return seed * middle_arithmetic2(seed, reduction);
}
float seed_reduction_arithmetic_div(const float seed, const float reduction) 
{
	return seed / middle_arithmetic2(seed, reduction);
}
float seed_reduction_hoelder_add(const float seed, const float reduction) 
{
	return seed + middle_hoelder2(seed, reduction);
}
float seed_reduction_hoelder_sub(const float seed, const float reduction) 
{
	return seed - middle_hoelder2(seed, reduction);
}
float seed_reduction_hoelder_mul(const float seed, const float reduction) 
{
	return seed * middle_hoelder2(seed, reduction);
}
float seed_reduction_hoelder_div(const float seed, const float reduction) 
{
	return seed / middle_hoelder2(seed, reduction);
}
float seed_reduction_geometric_add(const float seed, const float reduction) 
{
	return seed + middle_geometric2(seed, reduction);
}
float seed_reduction_geometric_sub(const float seed, const float reduction) 
{
	return seed - middle_geometric2(seed, reduction);
}
float seed_reduction_geometric_mul(const float seed, const float reduction) 
{
	return seed * middle_geometric2(seed, reduction);
}
float seed_reduction_geometric_div(const float seed, const float reduction) 
{
	return seed / middle_geometric2(seed, reduction);
}
float seed_reduction_cubic_add(const float seed, const float reduction) 
{
	return seed + middle_cubic2(seed, reduction);
}
float seed_reduction_cubic_sub(const float seed, const float reduction) 
{
	return seed - middle_cubic2(seed, reduction);
}
float seed_reduction_cubic_mul(const float seed, const float reduction) 
{
	return seed * middle_cubic2(seed, reduction);
}
float seed_reduction_cubic_div(const float seed, const float reduction) 
{
	return seed / middle_cubic2(seed, reduction);
}
float seed_reduction_quad_add(const float seed, const float reduction) 
{
	return seed + middle_quad2(seed, reduction);
}
float seed_reduction_quad_sub(const float seed, const float reduction) 
{
	return seed - middle_quad2(seed, reduction);
}
float seed_reduction_quad_mul(const float seed, const float reduction) 
{
	return seed * middle_quad2(seed, reduction);
}
float seed_reduction_quad_div(const float seed, const float reduction) 
{
	return seed / middle_quad2(seed, reduction);
}
float seed_reduction_harmonic_add(const float seed, const float reduction) 
{
	return seed + middle_harmonic2(seed, reduction);
}
float seed_reduction_harmonic_sub(const float seed, const float reduction) 
{
	return seed - middle_harmonic2(seed, reduction);
}
float seed_reduction_harmonic_mul(const float seed, const float reduction) 
{
	return seed * middle_harmonic2(seed, reduction);
}
float seed_reduction_harmonic_div(const float seed, const float reduction) 
{
	return seed / middle_harmonic2(seed, reduction);
}

void filter_noise_gauss(noise_t *noise, float deviation) {
	
	int _w = noise->map->config->cnt;
	int _h = noise->map->config->size;
	
	const int kernelside = _w;
	float * gausskernel = malloc(kernelside*kernelside * sizeof(float));
	
	float useddeviavtion = 2*deviation*deviation;
	float base=1.f/(M_PI*useddeviavtion);

	int pxrange = (_w >> 1);
	for ( int pry = -pxrange, ky = 0; pry <= (int)pxrange; ++pry, ++ky ){
		int y_2 = pry*pry;
		for ( int prx = -pxrange, kx = 0; prx <= (int)pxrange; ++prx, ++kx ){
			int x_2 = prx*prx;
			gausskernel[ky * kernelside + kx] = base * expf(-((y_2+x_2)/useddeviavtion));
		}
	}
	
	
	float fref;
	array_error_t array_res;
	float noise_min = FLT_MAX;
	float noise_max = FLT_MIN;
	//float gauss_max = gausskernel[pxrange * kernelside + pxrange];
	for (unsigned int h = _h; h--;){
	  for (unsigned int w = _w; w--;){
			array_res = farray2D_get(noise->map, w, h, &fref);
			if(array_res==ARRAY_ERR_OK){
				float factor = gausskernel[h * kernelside + w];
				float noiseval = interpolate_lin(fref, noise->min, 0.f, noise->max, 1.f)*factor;
				//if ( factor != 0.f ) {
				//	noiseval = fref*(1.f-(factor/gauss_max));
				//}
				noise_min = fminf(noise_min, noiseval);
				noise_max = fmaxf(noise_max, noiseval);
				farray2D_set(noise->map, w, h, noiseval);
			}
	    }
	}
	
	noise->min = noise_min;
	noise->max = noise_max;
	
	free(gausskernel);
}

void filter_noise_circle(noise_t *noise, float radius) {
	
	int _w = noise->map->config->cnt;
	int _h = noise->map->config->size;
	
	int pxrange = (_w >> 1);
	
	float fref;
	array_error_t array_res;

	float _len = pxrange;
	const float max_len = sqrtf(2*(_len*_len));
	const float inner_limit = max_len * radius;
	float noise_min = FLT_MAX;
	float noise_max = FLT_MIN;
	for (int h = _h; h--;){
	  for (int w = _w; w--;){
			array_res = farray2D_get(noise->map, w, h, &fref);
			if(array_res==ARRAY_ERR_OK){
				float noiseval = 0.f;
				
				float x = _len-w;
				float y = _len-h;
				float cur_len = sqrtf((x*x) + (y*y));
				if ( cur_len <= inner_limit ) {
					float factor = 1.f-(cur_len/inner_limit);
					noiseval = interpolate_lin(fref, noise->min, 0.f, noise->max, 1.f)*factor;
				}
				noise_min = fminf(noise_min, noiseval);
				noise_max = fmaxf(noise_max, noiseval);

				farray2D_set(noise->map, w, h, noiseval);
			}
	    }
	}
	
	noise->min = noise_min;
	noise->max = noise_max;

}

