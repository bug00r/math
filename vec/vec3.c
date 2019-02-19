
const size_t vec3_size = sizeof(vec3_t);

void 
vec3_zero(vec3_t *  dest){
	dest->x = 0.f;
	dest->y = 0.f;
	dest->z = 0.f;
}

vec3_t * 
vec3_zero_new(){
	vec3_t * newvec = malloc(vec3_size);
	vec3_zero(newvec);
	return newvec;
}

void 
vec3_set_values(vec3_t *  dest, const float x, const float y, const float z){
	dest->x = x;
	dest->y = y;
	dest->z = z;
}

bool 
vec3_equals( const vec3_t *  v, const vec3_t *   v2){
	return ( v == v2 ) ||
		   (( v->x == v2->x ) &&
		   ( v->y == v2->y ) &&
		   ( v->z == v2->z ));
}


void 
vec3_cross( vec3_t *   v, const vec3_t *   v2){
	float temp[3] = {
		((v->y * v2->z) - (v->z * v2->y)),
		((v->z * v2->x) - (v->x * v2->z)),
		((v->x * v2->y) - (v->y * v2->x))
	};
	 v->x = temp[0];
	 v->y = temp[1];
	 v->z = temp[2];
}

vec3_t * 
vec3_cross_new( const vec3_t *   v, const vec3_t *   v2){
	vec3_t *newvec = vec3_zero_new();
	newvec->x = ((v->y * v2->z) - (v->z * v2->y));
	newvec->y = ((v->z * v2->x) - (v->x * v2->z));
	newvec->z = ((v->x * v2->y) - (v->y * v2->x));
	return newvec;
}

void 
vec3_cross_dest(vec3_t *  dest, const vec3_t *   v, const vec3_t *   v2){
	dest->x = ((v->y * v2->z) - (v->z * v2->y));
	dest->y = ((v->z * v2->x) - (v->x * v2->z));
	dest->z = ((v->x * v2->y) - (v->y * v2->x));
}

void 
vec3_mul( vec3_t *   v, const float skalar){
	v->x *= skalar;
	v->y *= skalar;
	v->z *= skalar;
}

vec3_t * 
vec3_mul_dest(vec3_t *  dest, const vec3_t *   v, const float skalar){	
	dest->x = v->x * skalar;
	dest->y = v->y * skalar;
	dest->z = v->z * skalar;
	return dest;
}

vec3_t * 
vec3_mul_new( const vec3_t *   v, const float skalar){
	return vec3_mul_dest(vec3_zero_new(), v, skalar);
}

float 
vec3_vec3mul( const vec3_t *   v, const vec3_t *   v2){
	return ((v->x*v2->x)+(v->y*v2->y)+(v->z*v2->z));
}

bool 
vec3_isorthogonal( const vec3_t *   v, const vec3_t *   v2){
	return vec3_vec3mul(v, v2) == 0.f;
}

float 
vec3_spat( const vec3_t *   v, const vec3_t *   v2, const vec3_t *   v3){
	vec3_t cross;
	vec3_cross_dest(&cross,v, v2);
	return vec3_vec3mul(&cross, v3);
}

float 
vec3_length( const vec3_t *  v){
	return sqrt((v->x*v->x) + (v->y*v->y) + (v->z*v->z));
}

vec3_t * 
vec3_copy_new( const vec3_t *   v){
	return vec3_copy_dest(vec3_zero_new(), v);
}

vec3_t * 
vec3_copy_dest(vec3_t *  dest, const vec3_t *   v){
	dest->x = v->x;
	dest->y = v->y;
	dest->z = v->z;
	return dest;
}

void 
vec3_negate(vec3_t *   v){
	v->x *= -1;
	v->y *= -1;
	v->z *= -1;
}

vec3_t * 
vec3_negate_dest(vec3_t *   dest, const vec3_t *   v){
	dest->x = -(v->x);
	dest->y = -(v->y);
	dest->z = -(v->z);
	return dest;
}

vec3_t* 
vec3_negate_new(const vec3_t *   v){
	return vec3_negate_dest(vec3_zero_new(), v);
}

void 
vec3_add( vec3_t *  v1,  const vec3_t *   v2){
	v1->x += v2->x;
	v1->y += v2->y;
	v1->z += v2->z;
}

vec3_t * 
vec3_add_dest( vec3_t *  dest, const vec3_t *  v1,  const vec3_t *   v2){
	dest->x = v1->x + v2->x;
	dest->y = v1->y + v2->y;
	dest->z = v1->z + v2->z;
	return dest;
}

vec3_t * 
vec3_add_new( const vec3_t *   v1,  const vec3_t *   v2) {
	return vec3_add_dest(vec3_zero_new(), v1, v2);
}

vec3_t * vec3_add_n_dest(vec3_t *  dest, const int cntvecs, ...){
	va_list args;
	va_start(args, cntvecs);
	
	float res_x = 0.f;
	float res_y = 0.f;
	float res_z = 0.f;
	
	vec3_t * vec;
	for (int curvec = 0; curvec < cntvecs; ++curvec){
		vec = va_arg(args, vec3_t *);
		res_x += vec->x;
		res_y += vec->y;
		res_z += vec->z;
	}
	va_end(args);
	dest->x = res_x;
	dest->y = res_y;
	dest->z = res_z;
	
	return dest;
}

vec3_t* vec3_add_n_new( const int cntvecs, ...){
	va_list args;
	va_start(args, cntvecs);
	
	float res_x = 0.f;
	float res_y = 0.f;
	float res_z = 0.f;
	
	vec3_t * vec;
	for (int curvec = 0; curvec < cntvecs; ++curvec){
		vec = va_arg(args, vec3_t *);
		res_x += vec->x;
		res_y += vec->y;
		res_z += vec->z;
	}
	va_end(args);
	vec3_t * dest = vec3_zero_new();
	dest->x = res_x;
	dest->y = res_y;
	dest->z = res_z;
	
	return dest;
}


void 
vec3_sub( vec3_t *  v1,  const vec3_t *   v2){
	v1->x -= v2->x;
	v1->y -= v2->y;
	v1->z -= v2->z;
}

vec3_t * 
vec3_sub_dest( vec3_t *  dest, const vec3_t *  v1,  const vec3_t *   v2){
	dest->x = v1->x - v2->x;
	dest->y = v1->y - v2->y;
	dest->z = v1->z - v2->z;
	return dest;
}

vec3_t * 
vec3_sub_new( const vec3_t *   v1,  const vec3_t *   v2) {
	return vec3_sub_dest(vec3_zero_new(), v1, v2);
}

vec3_t * vec3_sub_n_dest(vec3_t *  dest, const int cntvecs, ...){
	va_list args;
	va_start(args, cntvecs);
	
	float res_x = 0.f;
	float res_y = 0.f;
	float res_z = 0.f;
	
	vec3_t * vec;
	for (int curvec = 0; curvec < cntvecs; ++curvec){
		vec = va_arg(args, vec3_t *);
		res_x -= vec->x;
		res_y -= vec->y;
		res_z -= vec->z;
	}
	va_end(args);
	dest->x = res_x;
	dest->y = res_y;
	dest->z = res_z;
	
	return dest;
}

vec3_t* vec3_sub_n_new( const int cntvecs, ...){
	va_list args;
	va_start(args, cntvecs);
	
	float res_x = 0.f;
	float res_y = 0.f;
	float res_z = 0.f;
	
	vec3_t * vec;
	for (int curvec = 0; curvec < cntvecs; ++curvec){
		vec = va_arg(args, vec3_t *);
		res_x -= vec->x;
		res_y -= vec->y;
		res_z -= vec->z;
	}
	va_end(args);
	vec3_t * dest = vec3_zero_new();
	dest->x = res_x;
	dest->y = res_y;
	dest->z = res_z;
	
	return dest;
}

char * 
vec3_tostring(const vec3_t *  v){
	char * fmt = "vec3(x=%f, y=%f, z=%f)";
	int sz = snprintf(NULL, 0, fmt, v->x, v->y, v->z);
	size_t needbytes = (sz+1)*sizeof(char);
	char * buf = malloc(needbytes);
	snprintf(buf, needbytes, fmt, v->x, v->y, v->z);
	return buf;
}

void 
vec3_print( const vec3_t *  v){
	char *vec_string = vec3_tostring(v);
	printf("%s\n", vec_string);
	free(vec_string);
}

void 
vec3_normalize( vec3_t *  v){
	float length = vec3_length(v);
	vec3_mul(v, (1.0/length));
}

vec3_t * 
vec3_normalize_dest(vec3_t *  dest, const vec3_t *  v){
	vec3_copy_dest(dest, v);
	vec3_normalize(dest);
	return dest;
}

vec3_t * 
vec3_normalize_new( const vec3_t *  v){
	return vec3_normalize_dest(vec3_zero_new(), v);
}

float
vec3_angle( const vec3_t *  v, const vec3_t *  v2){
	return acos( vec3_vec3mul(v, v2) / ( vec3_length(v) * vec3_length(v2) ));
}