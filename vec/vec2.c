const size_t vec2_size = sizeof(vec2_t);

void 
vec2_zero(vec2_t *  dest){
	dest->x = 0.f;
	dest->y = 0.f;
}

vec2_t * 
vec2_zero_new(){
	vec2_t * newvec = malloc(vec2_size);
	vec2_zero(newvec);
	return newvec;
}

bool 
vec2_equals( const vec2_t *   v, const vec2_t *  v2){
	return ( v == v2 ) || (( v->x == v2->x ) && ( v->y == v2->y ));
}

float 
vec2_cross( const vec2_t *  v, const vec2_t *  v2){
	return (v->x*v2->y) - (v2->x*v->y);
}

void 
vec2_mul( vec2_t *   v, const float skalar){
	v->x *= skalar;
	v->y *= skalar;
}

vec2_t * 
vec2_mul_dest(vec2_t *  dest, const vec2_t *  v, const float skalar){	
	dest->x = v->x * skalar;
	dest->y = v->y * skalar;
	return dest;
}

vec2_t * 
vec2_mul_new( const vec2_t *  v, const float skalar){
	return vec2_mul_dest(vec2_zero_new(), v, skalar);
}

float 
vec2_vec2mul( const vec2_t *  v, const vec2_t *    v2){
	return ((v->x*v2->x)+(v->y*v2->y));
}

bool 
vec2_isorthogonal( const vec2_t *   v, const vec2_t *   v2){
	return vec2_vec2mul(v, v2) == 0.f;
}

float 
vec2_length( const vec2_t *   v){
	return sqrt((v->x*v->x) + (v->y*v->y));
}

vec2_t * 
vec2_copy_new( const vec2_t *   v){
	return vec2_copy_dest(vec2_zero_new(), v);
}

vec2_t * 
vec2_copy_dest(vec2_t *  dest, const vec2_t *   v){
	dest->x = v->x;
	dest->y = v->y;
	return dest;
}

void 
vec2_negate(vec2_t *   v){
	v->x *= -1;
	v->y *= -1;
}

vec2_t * 
vec2_negate_dest(vec2_t *   dest, const vec2_t *   v){
	dest->x = -(v->x);
	dest->y = -(v->y);
	return dest;
}

vec2_t* 
vec2_negate_new(const vec2_t *   v){
	return vec2_negate_dest(vec2_zero_new(), v);
}

void 
vec2_add( vec2_t *  v1,  const vec2_t *   v2){
	v1->x += v2->x;
	v1->y += v2->y;
}

vec2_t * 
vec2_add_dest(vec2_t *  dest, const vec2_t *  v1,  const vec2_t *   v2){
	dest->x = v1->x + v2->x;
	dest->y = v1->y + v2->y;
	return dest;
}

vec2_t * 
vec2_add_new( const vec2_t *   v1,  const vec2_t *   v2) {
	return vec2_add_dest(vec2_zero_new(), v1, v2);
}

vec2_t * vec2_add_n_dest(vec2_t *  dest, const int cntvecs, ...){
	va_list args;
	va_start(args, cntvecs);
	
	float res_x = 0.f;
	float res_y = 0.f;
	
	vec2_t * vec;
	for (int curvec = 0; curvec < cntvecs; ++curvec){
		vec = va_arg(args, vec2_t *);
		res_x += vec->x;
		res_y += vec->y;
	}
	va_end(args);
	dest->x = res_x;
	dest->y = res_y;
	
	return dest;
}

vec2_t* vec2_add_n_new( const int cntvecs, ...){
	va_list args;
	va_start(args, cntvecs);
	
	float res_x = 0.f;
	float res_y = 0.f;
	
	vec2_t * vec;
	for (int curvec = 0; curvec < cntvecs; ++curvec){
		vec = va_arg(args, vec2_t *);
		res_x += vec->x;
		res_y += vec->y;
	}
	va_end(args);
	vec2_t * dest = vec2_zero_new();
	dest->x = res_x;
	dest->y = res_y;
	
	return dest;
}

void 
vec2_sub( vec2_t *v1,  const vec2_t *   v2){
	v1->x -= v2->x;
	v1->y -= v2->y;
}

vec2_t * 
vec2_sub_dest(vec2_t * dest, const vec2_t *  v1,  const vec2_t *   v2){
	dest->x = v1->x - v2->x;
	dest->y = v1->y - v2->y;
	return dest;
}

vec2_t * 
vec2_sub_new( const vec2_t *   v1,  const vec2_t *   v2) {
	return vec2_sub_dest(vec2_zero_new(), v1, v2);
}

vec2_t * vec2_sub_n_dest(vec2_t *   dest, const int cntvecs, ...){
	va_list args;
	va_start(args, cntvecs);
	
	float res_x = 0.f;
	float res_y = 0.f;
	
	vec2_t * vec;
	for (int curvec = 0; curvec < cntvecs; ++curvec){
		vec = va_arg(args, vec2_t *);
		res_x -= vec->x;
		res_y -= vec->y;
	}
	va_end(args);
	dest->x = res_x;
	dest->y = res_y;
	
	return dest;
}

vec2_t* vec2_sub_n_new( const int cntvecs, ...){
	va_list args;
	va_start(args, cntvecs);
	
	float res_x = 0.f;
	float res_y = 0.f;
	
	vec2_t * vec;
	for (int curvec = 0; curvec < cntvecs; ++curvec){
		vec = va_arg(args, vec2_t *);
		res_x -= vec->x;
		res_y -= vec->y;
	}
	va_end(args);
	vec2_t * dest = vec2_zero_new();
	dest->x = res_x;
	dest->y = res_y;
	
	return dest;
}


char * 
vec2_tostring(const vec2_t *  v){
	char * fmt = "vec2(x=%f, y=%f)";
	int sz = snprintf(NULL, 0, fmt, v->x, v->y);
	size_t needbytes = (sz+1)*sizeof(char);
	char * buf = malloc(needbytes);
	snprintf(buf, needbytes, fmt, v->x, v->y);
	return buf;
}

void 
vec2_print( const vec2_t *   v){
	char *vec_string = vec2_tostring(v);
	printf("%s\n", vec_string);
	free(vec_string);
}


void 
vec2_normalize( vec2_t *   v){
	float length = vec2_length(v);
	vec2_mul(v, (1.0/length));
}

vec2_t * 
vec2_normalize_dest(vec2_t *   dest, const vec2_t *   v){
	vec2_copy_dest(dest, v);
	vec2_normalize(dest);
	return dest;
}

vec2_t * 
vec2_normalize_new( const vec2_t *   v){
	return vec2_normalize_dest(vec2_zero_new(), v);
}

float
vec2_angle( const vec2_t *   v, const vec2_t *   v2){
	return acos(vec2_vec2mul(v, v2) / ( vec2_length(v) * vec2_length(v2)));
}
