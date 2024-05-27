
#include "utilsmath.h"

static const float onedegrad = M_PI / 180.f;

int round_f(float num)
{
	return (int)(num < 0 ? (num - .5f) : (num + .5f));
}

float interpolate_lin(const float x, const float x0, const float f0, const float x1, const float f1){
	float result = 0.f;
	
	if ( f0 != 0.0f) {
		result += f0*((x1 - x)/(x1 - x0));
	} else {
		result = f0;
	}
	
	if ( f1 != 0.0f) {
		result += f1*((x - x0)/(x1 - x0));
	}
	
	return result;
}

int compare_floats(const void* a, const void* b){
    const float arg1 = *(const float*)a;
    const float arg2 = *(const float*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

float seedrndlh(const float lnum, const float hnum){
	return lnum + ((float)rand()/((float)(RAND_MAX)/(hnum-lnum)));
}

int seedrndlh_int(const int lnum, const int hnum){
	return lnum + ((int)rand()/((int)(RAND_MAX)/(hnum-lnum)));
}

float seedrnd(const float seed){
	return (((float)rand()/(float)(RAND_MAX)) * 2.f * seed) - seed;
}


void 
inside_mandelbrot_set(const float _Complex * point, const int cntiterations, MandelbrotPoint *result){
	float _Complex cur_Complex = 0.f + 0.f*I;
	float curabs;
	bool insinde = true;
	int i = 0;
	for(; i < cntiterations; ++i){
		cur_Complex = cpowf(cur_Complex, 2) + *point;
		curabs = cabsf(cur_Complex);
		if ( curabs > 2.f ){
			insinde = false;
			break;
		}
	}
	result->cpoint = cur_Complex;
	result->spoint = *point;
	result->abs = curabs;
	result->iterations = i;
	result->isin = insinde;
}

void 
inside_julia_set(const float _Complex *point, const float _Complex *c, const int cntiterations, JuliaPoint *result, 
				 float _Complex (*polyfunc)( const float _Complex *cp, const float _Complex *c))
{
	float _Complex cur_Complex = *point;
	float curabs;
	bool insinde = false;
	int i = 0;
	for(; i < cntiterations; ++i){
		//cur_Complex = cpowf(cur_Complex, 2) + *c;
		cur_Complex = (*polyfunc)(&cur_Complex, c);
		curabs = cabsf(cur_Complex);
		if ( curabs > 2.f ){
			insinde = true;
			break;
		}
	}
	result->iterations = i;
	result->isin = insinde;
	result->cpoint = cur_Complex;
	result->spoint = *point;
	result->abs = curabs;
}

float 
rad(const float degree) {
	return onedegrad * degree;
}

float 
rand_path_deg(const int maxdeg){
	float deg = (float)(rand() % maxdeg) + (rand()%100 * 0.01f);
	return (rand() % 2 == 0 ? -deg: deg);
}
#if defined(USE_VEC_3)

Vec3 * 
vec3_scale_dest(Vec3 * dest, const float scx, const float scy, const float scz){
	dest->x *= scx;
	dest->y *= scy;
	dest->z *= scz;
	return dest;
}

#endif

#if defined(USE_VEC_2) && defined(USE_MAT_2)

void 
mat_vec_mul_2(const Mat2* m, Vec2 * v){
	Vec2 temp = {v->x, v->y};
	v->x = (m->_11 * temp.x) + (m->_12 * temp.y);
	v->y = (m->_21 * temp.x) + (m->_22 * temp.y);
}

Vec2 * 
mat_vec_mul_2_new(const Mat2* m, const Vec2 * v){
	Vec2 * newvec = malloc(vec2_size);
	newvec->x = (m->_11 * v->x) + (m->_12 * v->y);
	newvec->y = (m->_21 * v->x) + (m->_22 * v->y);
	return newvec;
}

float 
place_of_vec3(const Vec3 * s, const Vec3 * e, const Vec3 * p){	
	return (p->x - s->x) * (e->y - s->y) - (p->y - s->y) * (e->x - s->x);
	#if 0
	Mat2 temp = { (p->x - s->x), (p->y - s->y), (e->x - s->x),(e->y - s->y)};
	return mat2_determinant(&temp);
	#endif
}

void 
is_inside_triangle(const Vec3 * v0, const Vec3 * v1, const Vec3 * v2, const Vec3 * p, Barycentric * bc){
	//top left edge test
	//bc->inside = true;
	bc->inside = false;
	const Vec3 *_v0 = v0, *_v1 = v1, *_v2=v2,*_p=p;
	//maybe we have a counter clockwise problem
	bc->w0_12 = (_p->x - _v1->x) * (_v2->y - _v1->y) - (_p->y - _v1->y) * (_v2->x - _v1->x);
	if (bc->w0_12 < 0.f) return;
	bc->w1_20 = (_p->x - _v2->x) * (_v0->y - _v2->y) - (_p->y - _v2->y) * (_v0->x - _v2->x);    
	if (bc->w1_20 < 0.f) return;
	bc->w2_01 = (_p->x - _v0->x) * (_v1->y - _v0->y) - (_p->y - _v0->y) * (_v1->x - _v0->x);
	if (bc->w2_01 < 0.f) return;
	
	//top left edge test
	//Vec3 edge0, edge1, edge2;
	//
	//vec3_sub_dest(&edge0, v2, v1);
	//vec3_sub_dest(&edge1, v0, v2);
	//vec3_sub_dest(&edge2, v1, v0);
	
	//counter clockwise
	//bc->inside = ( bc->w0_12 <= 0.f && bc->w1_20 <= 0.f && bc->w2_01 <= 0.f );
	//clockwise
	bc->inside = true; //( bc->w0_12 >= 0.f && bc->w1_20 >= 0.f && bc->w2_01 >= 0.f );
	//top left edge test
	//bc->inside &= (bc->w0_12 == 0.f ? ((edge0.y == 0.f && edge0.x > 0.f) || edge0.y > 0.f) : bc->w0_12 > 0.f );
	//bc->inside &= (bc->w1_20 == 0.f ? ((edge1.y == 0.f && edge1.x > 0.f) || edge1.y > 0.f) : bc->w1_20 > 0.f );
	//bc->inside &= (bc->w2_01 == 0.f ? ((edge2.y == 0.f && edge2.x > 0.f) || edge2.y > 0.f) : bc->w2_01 > 0.f );
	bc->bc0 = bc->w0_12 / bc->area;
	bc->bc1 = bc->w1_20 / bc->area;
	bc->bc2 = bc->w2_01 / bc->area;	
}

void 
print_barycentric(const Barycentric * bc){
	printf("w0_12:\t%f\n", bc->w0_12);
	printf("w1_20:\t%f\n", bc->w1_20);
	printf("w2_01:\t%f\n", bc->w2_01);
	printf("area:\t%f\n", bc->area);
	printf("bc0:\t%f\n", bc->bc0);
	printf("bc1:\t%f\n", bc->bc1);
	printf("bc2:\t%f\n", bc->bc2);
	printf("inside:\t%i\n", bc->inside);
}

#endif

float line_intersect_denominator(Vec2* _l1p1, Vec2* _l1p2, Vec2* _l2p1, Vec2* _l2p2) {
	Vec2* l1p1 = _l1p1;
	Vec2* l1p2 = _l1p2;
	Vec2* l2p1 = _l2p1;
	Vec2* l2p2 = _l2p2;

	return (l1p1->x - l1p2->x)*(l2p1->y - l2p2->y) - (l1p1->y - l1p2->y)*(l2p1->x - l2p2->x);

}

bool lines_intersect(Vec2* _l1p1, Vec2* _l1p2, Vec2* _l2p1, Vec2* _l2p2) {
	Vec2* l1p1 = _l1p1;
	Vec2* l1p2 = _l1p2;
	Vec2* l2p1 = _l2p1;
	Vec2* l2p2 = _l2p2;

	float denom = line_intersect_denominator(l1p1, l1p2, l2p1, l2p2);

	return (denom != 0.f);
}

bool lines_intersect_pt(Vec2 *intersec, Vec2* _l1p1, Vec2* _l1p2, Vec2* _l2p1, Vec2* _l2p2) {

	Vec2* l1p1 = _l1p1;
	Vec2* l1p2 = _l1p2;
	Vec2* l2p1 = _l2p1;
	Vec2* l2p2 = _l2p2;

	float denom = line_intersect_denominator(l1p1, l1p2, l2p1, l2p2);
	if (denom != 0.f && intersec) {
		//x1y2-y1x2
		float x1y2_y1x2 = (l1p1->x * l1p2->y) - (l1p1->y * l1p2->x);
		//x3y4-y3x4
		float x3y4_y3x4 = (l2p1->x * l2p2->y) - (l2p1->y * l2p2->x);
		//(x1y2-y1x2)(x3-x4)-(x1-x2)(x3y4-y3x4) / denom
		intersec->x = (x1y2_y1x2 * (l2p1->x - l2p2->x)) - ((l1p1->x - l1p2->x) * x3y4_y3x4);
		intersec->x /= denom;
		//(x1y2-y1x2)(y3-y4)-(y1-y2)(x3y4-y3x4) / denom
		intersec->y = (x1y2_y1x2 * (l2p1->y - l2p2->y)) - ((l1p1->y - l1p2->y) * x3y4_y3x4);
		intersec->y /= denom;
	}


	return denom != 0.f;
}

static void __mu_lineseg_intersec_raw(Vec2* l1p1, Vec2* l1p2, Vec2* l2p1, Vec2* l2p2, bool *intersect, Vec2 *intersect_pt) {

	*intersect = line_intersect_denominator(l1p1, l1p2, l2p1, l2p2);

	if ( *intersect ) {
		
		float 	x1 = l1p1->x,
				x2 = l1p2->x,
				x3 = l2p1->x,
				x4 = l2p2->x,
				y1 = l1p1->y,
				y2 = l1p2->y,
				y3 = l2p1->y,
				y4 = l2p2->y;

		float x1mx3 = x1 - x3,
			  x1mx2 = x1 - x2,
			  x3mx4 = x3 - x4,
			  y1my2 = y1 - y2,
			  y1my3 = y1 - y3,
			  y3my4 = y3 - y4;

		float t = ((x1mx3*y3my4) - (y1my3*x3mx4)) / ((x1mx2*y3my4) - (y1my2*x3mx4));

		float u = ((x1mx3*y1my2) - (y1my3*x1mx2)) / ((x1mx2*y3my4) - (y1my2*x3mx4));

		*intersect = (t >= 0.f && t <= 1.f && u >= 0.f && u <= 1.f);

		intersect_pt->x = x1 + (t*(x2-x1));
		intersect_pt->y = y1 + (t*(y2-y1));
	}

}

bool lineseg_intersect(Vec2* l1p1, Vec2* l1p2, Vec2* l2p1, Vec2* l2p2) {

	bool intersect;
	Vec2 intersect_pt;

	 __mu_lineseg_intersec_raw(l1p1, l1p2, l2p1, l2p2, &intersect, &intersect_pt);

	return intersect;
}

bool lineseg_intersect_pt(Vec2 *intersec, Vec2* l1p1, Vec2* l1p2, Vec2* l2p1, Vec2* l2p2) {
	
	bool intersect;
	
	__mu_lineseg_intersec_raw(l1p1, l1p2, l2p1, l2p2, &intersect,intersec);

	return intersect;
}


#if defined(USE_VEC_3) && defined(USE_MAT_3)

void 
mat_vec_mul_3(const Mat3* m, Vec3 * v){
	Vec3 temp = {v->x, v->y, v->z};
	v->x = (m->_11 * temp.x) + (m->_12 * temp.y) + (m->_13 * temp.z);
	v->y = (m->_21 * temp.x) + (m->_22 * temp.y) + (m->_23 * temp.z);
	v->z = (m->_31 * temp.x) + (m->_32 * temp.y) + (m->_33 * temp.z);
}


Vec3 * 
mat_vec_mul_3_new(const Mat3* m, const Vec3 * v){
	Vec3 * newvec = malloc(vec3_size);
	newvec->x = (m->_11 * v->x) + (m->_12 * v->y) + (m->_13 * v->z);
	newvec->y = (m->_21 * v->x) + (m->_22 * v->y) + (m->_23 * v->z);
	newvec->z = (m->_31 * v->x) + (m->_32 * v->y) + (m->_33 * v->z);
	return newvec;
}

Vec3 * mat_vec_mul_3_dest(Vec3 * dest, const Mat3 *  m, const Vec3 *  v) {
	Vec3 * newvec = dest;
	newvec->x = (m->_11 * v->x) + (m->_12 * v->y) + (m->_13 * v->z);
	newvec->y = (m->_21 * v->x) + (m->_22 * v->y) + (m->_23 * v->z);
	newvec->z = (m->_31 * v->x) + (m->_32 * v->y) + (m->_33 * v->z);
	return newvec;
}

Mat3 * 
create_rot_x_mat(const float degree){
	Mat3 * rotmat = malloc(mat3_size);
	const float radian = onedegrad * degree;
	const float sinus = sinf(radian);
	const float cosinus = cosf(radian);
	rotmat->_11 = 1.f;
	rotmat->_12 = 0.f;
	rotmat->_13 = 0.f;
	rotmat->_21 = 0.f;
	rotmat->_22 = cosinus;
	rotmat->_23 = -sinus;
	rotmat->_31 = 0.f;
	rotmat->_32 = sinus;
	rotmat->_33 = cosinus;
	return rotmat;
}

Mat3 * 
create_rot_x_mat_dest(Mat3 * dest, const float degree){
	Mat3 * rotmat = dest;
	const float radian = onedegrad * degree;
	const float sinus = sinf(radian);
	const float cosinus = cosf(radian);
	rotmat->_11 = 1.f;
	rotmat->_12 = 0.f;
	rotmat->_13 = 0.f;
	rotmat->_21 = 0.f;
	rotmat->_22 = cosinus;
	rotmat->_23 = -sinus;
	rotmat->_31 = 0.f;
	rotmat->_32 = sinus;
	rotmat->_33 = cosinus;
	return dest;
}

Mat3 * 
create_rot_y_mat(const float degree){
	Mat3 * rotmat = malloc(mat3_size);
	const float radian = onedegrad * degree;
	const float sinus = sinf(radian);
	const float cosinus = cosf(radian);
	rotmat->_11 = cosinus;
	rotmat->_12 = 0.f;
	rotmat->_13 = sinus;
	rotmat->_21 = 0.f;
	rotmat->_22 = 1.f;
	rotmat->_23 = 0.f;
	rotmat->_31 = -sinus;
	rotmat->_32 = 0.f;
	rotmat->_33 = cosinus;
	return rotmat;
}

Mat3 * 
create_rot_y_mat_dest(Mat3 * dest, const float degree){
	Mat3 * rotmat = dest;
	const float radian = onedegrad * degree;
	const float sinus = sinf(radian);
	const float cosinus = cosf(radian);
	rotmat->_11 = cosinus;
	rotmat->_12 = 0.f;
	rotmat->_13 = sinus;
	rotmat->_21 = 0.f;
	rotmat->_22 = 1.f;
	rotmat->_23 = 0.f;
	rotmat->_31 = -sinus;
	rotmat->_32 = 0.f;
	rotmat->_33 = cosinus;
	return dest;
}

Mat3 * 
create_rot_z_mat(const float degree){
	Mat3 * rotmat = malloc(mat3_size);
	const float radian = onedegrad * degree;
	const float sinus = sinf(radian);
	const float cosinus = cosf(radian);
	rotmat->_11 = cosinus;
	rotmat->_12 = -sinus;
	rotmat->_13 = 0.f;
	rotmat->_21 = sinus;
	rotmat->_22 = cosinus;
	rotmat->_23 = 0.f;
	rotmat->_31 = 0.f;
	rotmat->_32 = 0.f;
	rotmat->_33 = 1.f;
	return rotmat;
}

Mat3 * 
create_rot_z_mat_dest(Mat3 * dest, const float degree){
	Mat3 * rotmat = dest;
	const float radian = onedegrad * degree;
	const float sinus = sinf(radian);
	const float cosinus = cosf(radian);
	rotmat->_11 = cosinus;
	rotmat->_12 = -sinus;
	rotmat->_13 = 0.f;
	rotmat->_21 = sinus;
	rotmat->_22 = cosinus;
	rotmat->_23 = 0.f;
	rotmat->_31 = 0.f;
	rotmat->_32 = 0.f;
	rotmat->_33 = 1.f;
	return dest;
}

#endif

#if defined(USE_VEC_3) && defined(USE_MAT_4)

float 
transform_point(const Mat4 *  m, Vec3 *  v){
	Vec3 temp = {
		(v->x * m->_11) + (v->y * m->_12) + (v->z * m->_13) + m->_14,
		(v->x * m->_21) + (v->y * m->_22) + (v->z * m->_23) + m->_24,
		(v->x * m->_31) + (v->y * m->_32) + (v->z * m->_33) + m->_34
	};
	float weight = (v->x * m->_41) + (v->y * m->_42) + (v->z * m->_43) + m->_44;
	if (weight != 1.f && weight != 0.f){
		temp.x /= weight;
		temp.y /= weight;
		temp.z /= weight;
	}
	v->x = temp.x;
	v->y = temp.y;
	v->z = temp.z;
	return weight;
}

Vec3 * 
transform_point_new(const Mat4 *  m, const Vec3 *  v){
	Vec3 * newvec = vec3_copy_new(v);
	transform_point(m, newvec); //weight ignored useless!!!
	return newvec;
}

float transform_point_dest(Vec3 *  dest, const Mat4 *  m, const Vec3 *  v){

	dest->x = (v->x * m->_11) + (v->y * m->_12) + (v->z * m->_13) + m->_14;
	dest->y = (v->x * m->_21) + (v->y * m->_22) + (v->z * m->_23) + m->_24;
	dest->z = (v->x * m->_31) + (v->y * m->_32) + (v->z * m->_33) + m->_34;
	float weight = (v->x * m->_41) + (v->y * m->_42) + (v->z * m->_43) + m->_44;
	if (weight != 1.f && weight != 0.f){
		weight = 1.f/weight;
		dest->x *= weight;
		dest->y *= weight;
		dest->z *= weight;
	}
	return weight;
	
	//vec3_copy_dest(dest, v);
	//return transform_point(m, dest);
}

float mu_point_plane_distance(Vec3 *_point, Vec3 *_plane_p1, Vec3 *_plane_p2, Vec3 *_plane_p3) {
	Vec3 * p = _point;
	Vec3 * pp1 = _plane_p1;
	Vec3 * pp2 = _plane_p2;
	Vec3 * pp3 = _plane_p3;

	Vec3 dvec_p21;
	Vec3 dvec_p31;
	Vec3 normal;

	vec3_sub_dest(&dvec_p21, pp2, pp1);
	vec3_sub_dest(&dvec_p31, pp3, pp1);

	vec3_cross_dest(&normal, &dvec_p21, &dvec_p31);

	return mu_point_plane_distance_normal(p, pp1, &normal);
}

float mu_point_plane_distance_normal(Vec3 *_point, Vec3 *_plane_point, Vec3 *_normal) {
	Vec3 * p = _point;
	Vec3 * pp = _plane_point;
	Vec3 * normal = _normal;

	Vec3 p_pp1_sub;
	vec3_sub_dest(&p_pp1_sub, p, pp);

	return vec3_vec3mul(normal, &p_pp1_sub) / vec3_length(normal);
}

bool mu_line_plane_intersection(Vec3 *_intersect, Vec3 * _line_p1, Vec3 * _line_p2, Vec3 * _plane_p1, Vec3 * _plane_p2, Vec3 * _plane_p3) {
	Vec3 * pp1 = _plane_p1;
	Vec3 * pp2 = _plane_p2;
	Vec3 * pp3 = _plane_p3;
	Vec3 * lp1 = _line_p1;
	Vec3 * lp2 = _line_p2;
	Vec3 * inter = _intersect;

	// redundant normal vector calc => outsourcing
	Vec3 dvec_p21;
	Vec3 dvec_p31;
	Vec3 normal;

	vec3_sub_dest(&dvec_p21, pp2, pp1);
	vec3_sub_dest(&dvec_p31, pp3, pp1);

	vec3_cross_dest(&normal, &dvec_p21, &dvec_p31);

	

	/*Vec3 dvec_lp21;
	vec3_sub_dest(&dvec_lp21, lp2, lp1);
	vec3_normalize(&dvec_lp21);

	float n_mul_a = vec3_vec3mul(&normal, &dvec_lp21);
	bool intersects = (n_mul_a != 0.f);

	if ( intersects ) {
		Vec3 r0_sub_r1;
		vec3_sub_dest(&r0_sub_r1, pp1, lp1);

		vec3_mul_dest(inter, &dvec_lp21, vec3_vec3mul(&normal, &r0_sub_r1) / n_mul_a);
		vec3_add(inter, lp1);
	}

	return intersects;*/
	return mu_line_plane_intersection_normal(inter, lp1, lp2, pp1, &normal);

}
//Vec3 *_point, Vec3 *_plane_point, Vec3 *_normal
bool mu_line_plane_intersection_normal(Vec3 *intersect, Vec3 *_line_p1, Vec3 *_line_p2, Vec3 * _point, Vec3 *_normal) {
	Vec3 * pp1 = _point;
	Vec3 * lp1 = _line_p1;
	Vec3 * lp2 = _line_p2;
	Vec3 * inter = intersect;
	Vec3 * normal = _normal;

	Vec3 dvec_lp21;
	vec3_sub_dest(&dvec_lp21, lp2, lp1);
	vec3_normalize(&dvec_lp21);

	float n_mul_a = vec3_vec3mul(normal, &dvec_lp21);
	bool intersects = (n_mul_a != 0.f);

	if ( intersects ) {
		Vec3 r0_sub_r1;
		vec3_sub_dest(&r0_sub_r1, pp1, lp1);

		vec3_mul_dest(inter, &dvec_lp21, vec3_vec3mul(normal, &r0_sub_r1) / n_mul_a);
		vec3_add(inter, lp1);
	}

	return intersects;
}

float polygon_area_2D(Vec2 *_points, size_t _cntPoints)
{
	Vec2 *points = _points;
	size_t cntPoints =_cntPoints;

	float polyarea = 0.f;
	Mat2 matrix;
	Vec2 *p1, *p2;
	for ( size_t curPt = 1; curPt <= cntPoints; curPt++)
	{
		if ( curPt == cntPoints )
		{
			p1 = &points[curPt-1];
			p2 = &points[0];
		} else 
		{
			p1 = &points[curPt-1];
			p2 = &points[curPt];
		}

		matrix = (Mat2){ p1->x, p2->x, p1->y, p2->y};
		polyarea += mat2_determinant(&matrix);
	}

	return polyarea * 0.5f;
}

bool polygon_2D_is_clockwise(Vec2 *points, size_t cntPoints)
{
	return polygon_area_2D(points, cntPoints) < 0.f;
}

#endif
