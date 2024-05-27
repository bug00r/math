const size_t vec2_size = sizeof(Vec2);

void 
vec2_zero(Vec2 *  dest){
	dest->x = 0.f;
	dest->y = 0.f;
}

Vec2 * 
vec2_zero_new(){
	Vec2 * newvec = malloc(vec2_size);
	vec2_zero(newvec);
	return newvec;
}

bool 
vec2_equals( const Vec2 *   v, const Vec2 *  v2){
	return ( v == v2 ) || (( v->x == v2->x ) && ( v->y == v2->y ));
}

float 
vec2_cross( const Vec2 *  v, const Vec2 *  v2){
	return (v->x*v2->y) - (v2->x*v->y);
}

void 
vec2_mul( Vec2 *   v, const float skalar){
	v->x *= skalar;
	v->y *= skalar;
}

Vec2 * 
vec2_mul_dest(Vec2 *  dest, const Vec2 *  v, const float skalar){	
	dest->x = v->x * skalar;
	dest->y = v->y * skalar;
	return dest;
}

Vec2 * 
vec2_mul_new( const Vec2 *  v, const float skalar){
	return vec2_mul_dest(vec2_zero_new(), v, skalar);
}

float 
vec2_vec2mul( const Vec2 *  v, const Vec2 *    v2){
	return ((v->x*v2->x)+(v->y*v2->y));
}

bool 
vec2_isorthogonal( const Vec2 *   v, const Vec2 *   v2){
	return vec2_vec2mul(v, v2) == 0.f;
}

float 
vec2_length( const Vec2 *   v){
	return sqrt((v->x*v->x) + (v->y*v->y));
}

Vec2 * 
vec2_copy_new( const Vec2 *   v){
	return vec2_copy_dest(vec2_zero_new(), v);
}

Vec2 * 
vec2_copy_dest(Vec2 *  dest, const Vec2 *   v){
	dest->x = v->x;
	dest->y = v->y;
	return dest;
}

void 
vec2_negate(Vec2 *   v){
	v->x *= -1;
	v->y *= -1;
}

Vec2 * 
vec2_negate_dest(Vec2 *   dest, const Vec2 *   v){
	dest->x = -(v->x);
	dest->y = -(v->y);
	return dest;
}

Vec2* 
vec2_negate_new(const Vec2 *   v){
	return vec2_negate_dest(vec2_zero_new(), v);
}

void 
vec2_add( Vec2 *  v1,  const Vec2 *   v2){
	v1->x += v2->x;
	v1->y += v2->y;
}

Vec2 * 
vec2_add_dest(Vec2 *  dest, const Vec2 *  v1,  const Vec2 *   v2){
	dest->x = v1->x + v2->x;
	dest->y = v1->y + v2->y;
	return dest;
}

Vec2 * 
vec2_add_new( const Vec2 *   v1,  const Vec2 *   v2) {
	return vec2_add_dest(vec2_zero_new(), v1, v2);
}

Vec2 * vec2_add_n_dest(Vec2 *  dest, const int cntvecs, ...){
	va_list args;
	va_start(args, cntvecs);
	
	float res_x = 0.f;
	float res_y = 0.f;
	
	Vec2 * vec;
	for (int curvec = 0; curvec < cntvecs; ++curvec){
		vec = va_arg(args, Vec2 *);
		res_x += vec->x;
		res_y += vec->y;
	}
	va_end(args);
	dest->x = res_x;
	dest->y = res_y;
	
	return dest;
}

Vec2* vec2_add_n_new( const int cntvecs, ...){
	va_list args;
	va_start(args, cntvecs);
	
	float res_x = 0.f;
	float res_y = 0.f;
	
	Vec2 * vec;
	for (int curvec = 0; curvec < cntvecs; ++curvec){
		vec = va_arg(args, Vec2 *);
		res_x += vec->x;
		res_y += vec->y;
	}
	va_end(args);
	Vec2 * dest = vec2_zero_new();
	dest->x = res_x;
	dest->y = res_y;
	
	return dest;
}

void 
vec2_sub( Vec2 *v1,  const Vec2 *   v2){
	v1->x -= v2->x;
	v1->y -= v2->y;
}

Vec2 * 
vec2_sub_dest(Vec2 * dest, const Vec2 *  v1,  const Vec2 *   v2){
	dest->x = v1->x - v2->x;
	dest->y = v1->y - v2->y;
	return dest;
}

Vec2 * 
vec2_sub_new( const Vec2 *   v1,  const Vec2 *   v2) {
	return vec2_sub_dest(vec2_zero_new(), v1, v2);
}

Vec2 * vec2_sub_n_dest(Vec2 *   dest, const int cntvecs, ...){
	va_list args;
	va_start(args, cntvecs);
	
	float res_x = 0.f;
	float res_y = 0.f;
	
	Vec2 * vec;
	for (int curvec = 0; curvec < cntvecs; ++curvec){
		vec = va_arg(args, Vec2 *);
		res_x -= vec->x;
		res_y -= vec->y;
	}
	va_end(args);
	dest->x = res_x;
	dest->y = res_y;
	
	return dest;
}

Vec2* vec2_sub_n_new( const int cntvecs, ...){
	va_list args;
	va_start(args, cntvecs);
	
	float res_x = 0.f;
	float res_y = 0.f;
	
	Vec2 * vec;
	for (int curvec = 0; curvec < cntvecs; ++curvec){
		vec = va_arg(args, Vec2 *);
		res_x -= vec->x;
		res_y -= vec->y;
	}
	va_end(args);
	Vec2 * dest = vec2_zero_new();
	dest->x = res_x;
	dest->y = res_y;
	
	return dest;
}


char * 
Vec2ostring(const Vec2 *  v){
	char * fmt = "vec2(x=%f, y=%f)";
	int sz = snprintf(NULL, 0, fmt, v->x, v->y);
	size_t needbytes = (sz+1)*sizeof(char);
	char * buf = malloc(needbytes);
	snprintf(buf, needbytes, fmt, v->x, v->y);
	return buf;
}

void 
vec2_print( const Vec2 *   v){
	char *vec_string = Vec2ostring(v);
	printf("%s\n", vec_string);
	free(vec_string);
}


void 
vec2_normalize( Vec2 *   v){
	float length = vec2_length(v);
	vec2_mul(v, (1.0/length));
}

Vec2 * 
vec2_normalize_dest(Vec2 *   dest, const Vec2 *   v){
	vec2_copy_dest(dest, v);
	vec2_normalize(dest);
	return dest;
}

Vec2 * 
vec2_normalize_new( const Vec2 *   v){
	return vec2_normalize_dest(vec2_zero_new(), v);
}

float
vec2_angle( const Vec2 *   v, const Vec2 *   v2){
	return acos(vec2_vec2mul(v, v2) / ( vec2_length(v) * vec2_length(v2)));
}
