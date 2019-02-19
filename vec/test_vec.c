#if 0
/**
	This is a Test programm for vec 2 and 3 implementation.
*/
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "vec.h"

int 
main() {
	#ifdef USE_VEC_2
		#ifdef debug
			printf("Start testing vec2:\n");
		#endif
		
		
		#if 0
			//Test nzero vector
		#endif
		
		vec2_t * new_zero = vec2_zero_new();
		
		assert(new_zero->x == 0.0f);
		assert(new_zero->y == 0.0f);
		
		new_zero->x = 2.f;
		vec2_zero(new_zero);
		
		assert(new_zero->x == 0.0f);
		assert(new_zero->y == 0.0f);
		
		free(new_zero);
		#if 0
			//Test if Vector struct works
		#endif
		
		vec2_t myvec = {1.0f, 2.0f};
		
		assert(myvec.x == 1.0f);
		assert(myvec.y == 2.0f);
		
		#if 0
			//Test if Vecor to string method
		#endif
		
		char * string = vec2_tostring(&myvec);
		#ifdef debug
			printf("result vec2 tostring: \"%s\"\n",string);
		#endif
		free(string);
		
		#if 0
			//Test if Vecor additions
		#endif
		
		vec2_t myvec2 = {1.1f, 1.1f};
		
		vec2_add(&myvec, &myvec2);
		
		assert(myvec.x == 2.1f);
		assert(myvec.y == 3.1f);
		
		vec2_t *myvec3 = vec2_add_new(&myvec, &myvec2);
		
		//compare with floating point issue (could be realized into string format and compare as strings=>slow) this is enough for us
		assert(myvec3->x >= 3.199 &&  myvec3->x <= 3.200001);
		assert(myvec3->y >= 4.199 &&  myvec3->y <= 4.200001);
		
		free(myvec3);
		
		#if 0
			//Test if Vecor difference
		#endif
		
		vec2_t myvec_sub = {2.0f, 2.0f};
		vec2_t myvec_sub2 = {1.0f, 1.0f};
		
		vec2_sub(&myvec_sub, &myvec_sub2);
		
		assert(myvec_sub.x == 1.0f);
		assert(myvec_sub.y == 1.0f);
		
		vec2_t *myvec3_sub = vec2_sub_new(&myvec_sub, &myvec_sub2);
		
		//compare with floating point issue (could be realized into string format and compare as strings=>slow) this is enough for us
		assert(myvec3_sub->x >= 0.0f &&  myvec3_sub->x <= 1.0);
		assert(myvec3_sub->y >= 0.0f &&  myvec3_sub->y <= 1.0);
		
		free(myvec3_sub);
		
		
		#if 0
			//Test if Vecor negation
		#endif
		
		vec2_t myvec_neg = {1.0f, 2.0f};
		
		vec2_negate(&myvec_neg);
		
		assert(myvec_neg.x == -1.0f);
		assert(myvec_neg.y == -2.0f);
		
		vec2_t * myvec_neg_new = vec2_negate_new(&myvec_neg);
		
		assert(myvec_neg_new->x == 1.0f);
		assert(myvec_neg_new->y == 2.0f);
		
		free(myvec_neg_new);
		
		#if 0
			//Test Vector copy
		#endif
		
		vec2_t myvec_cpy = {5.0f, 6.0f};
		
		vec2_t * copy = vec2_copy_new(&myvec_cpy);
		
		assert(&myvec_cpy != copy);
		assert(myvec_cpy.x == copy->x);
		assert(myvec_cpy.y == copy->y);
		
		free(copy);
		
		#if 0
			//Test Vector length
		#endif
		
		vec2_t myvec_len = {5.0f, 6.0f};
		float length = vec2_length(&myvec_len);
		assert(length == 7.8102496759066543941297227357591f);
		
		#if 0
			//Test Vector multiplications
		#endif
		
		vec2_t vec_mul = {2.0f, 3.0f};
		vec2_t vec_mul2 = {2.0f, 3.0f};
		float factor = 2.0f;
		
		float skalarproduct = vec2_vec2mul(&vec_mul, &vec_mul2);
		assert(skalarproduct == 13.0f);
		
		vec2_t * mulres = vec2_mul_new(&vec_mul, factor);
		assert(mulres->x == 4.0f);
		assert(mulres->y == 6.0f);
		
		free(mulres);
		
		vec2_mul(&vec_mul, factor);
		
		assert(vec_mul.x == 4.0f);
		assert(vec_mul.y == 6.0f);
		
		#if 0
			//Test Vector normalisation
		#endif
		
		vec2_t vec_norm = {2.0f, 3.0f};
		vec2_normalize(&vec_norm);
		
		assert(vec_norm.x == 0.554700196225229122018341733457f);
		assert(vec_norm.y == 0.8320502943378436830275126001855f);
		
		float norm_len = vec2_length(&vec_norm);
		assert(norm_len == 1.0f);
		
		vec2_t vec_norm2 = {2.0f, 3.0f};
		vec2_t * normalized = vec2_normalize_new(&vec_norm2);
		
		assert(normalized->x == 0.554700196225229122018341733457f);
		assert(normalized->y == 0.8320502943378436830275126001855f);
		
		norm_len = vec2_length(normalized);
		assert(norm_len == 1.0f);
		free(normalized);
		#if 0
			//Test Vector 2D Cross product
		#endif
		
		vec2_t vec_cross = {2.0f, 3.0f};
		vec2_t vec_cross2 = {1.0f, 2.0f};
		
		float result = vec2_cross(&vec_cross, &vec_cross2);
		
		assert(result == 1.0f);
		
		#if 0
			//Test Vector 2D angle
		#endif
		
		vec2_t vec2_angle1 = {0.0f, 1.0f};
		vec2_t vec2_angle2 = {1.0f, 0.0f};
		
		float _vec2_angle_rad = vec2_angle(&vec2_angle1, &vec2_angle2);
		float _vec2_degree = _vec2_angle_rad * (180 / M_PI);
		assert(_vec2_degree <= 90.0001f && _vec2_degree >= 90.f );
		
		#if 0
			//Test Vector 2D equals
		#endif
		
		vec2_t vec2_eq = {0.0f, 1.0f};
		vec2_t vec2_eq1 = {1.0f, 0.0f};
		vec2_t vec2_eq2 = {1.0f, 0.0f};
		
		assert(!vec2_equals(&vec2_eq, &vec2_eq1));
		assert(vec2_equals(&vec2_eq1, &vec2_eq1));
		assert(vec2_equals(&vec2_eq1, &vec2_eq2));
		
		#if 0
			//Test Vector 2D orthogonality
		#endif
		
		assert(vec2_isorthogonal(&vec2_eq, &vec2_eq1));
		assert(!vec2_isorthogonal(&vec2_eq, &vec2_eq));
		
		#if 0
			//Test Vector 2D multiple addition and subtraction
		#endif
		
		vec2_t n_result;
		vec2_t *n_result_new;
		vec2_t n1 = {0.0f, 1.0f};
		vec2_t n2 = {1.0f, 1.0f};
		vec2_t n3 = {1.0f, 0.0f};
		vec2_t n4 = {0.5f, 0.5f};
		
		n_result = *vec2_add_n_dest(&n_result, 4, &n1, &n2, &n3, &n4);
		
		n_result_new = vec2_add_n_new( 4, &n1, &n2, &n3, &n4);
		
		assert(n_result.x == 2.5f);
		assert(n_result.y == 2.5f);
		
		assert(n_result_new->x == 2.5f);
		assert(n_result_new->y == 2.5f);
		
		free(n_result_new);
		
		n_result = *vec2_sub_n_dest(&n_result, 4, &n1, &n2, &n3, &n4);
		
		n_result_new = vec2_sub_n_new( 4, &n1, &n2, &n3, &n4);
		
		assert(n_result.x == -2.5f);
		assert(n_result.y == -2.5f);
		
		assert(n_result_new->x == -2.5f);
		assert(n_result_new->y == -2.5f);
		
		free(n_result_new);
		#ifdef debug
			printf("End testing vec2:\n");
		#endif
	#endif
	
	#ifdef USE_VEC_3
		#ifdef debug
			printf("Start testing vec3:\n");
		#endif
		
		#if 0
			//Test nzero vector
		#endif
		
		vec3_t * new_zero3 = vec3_zero_new();
		
		assert(new_zero3->x == 0.0f);
		assert(new_zero3->y == 0.0f);
		assert(new_zero3->z == 0.0f);
		
		new_zero3->x = 2.f;
		new_zero3->z = 2.f;
		vec3_zero(new_zero3);
		
		assert(new_zero3->x == 0.0f);
		assert(new_zero3->y == 0.0f);
		assert(new_zero3->z == 0.0f);
		
		free(new_zero3);
		
		#if 0
			//Test if Vector struct works
		#endif
		
		vec3_t _myvec = {1.0f, 2.0f, 3.0f};
		
		assert(_myvec.x == 1.0f);
		assert(_myvec.y == 2.0f);
		assert(_myvec.z == 3.0f);
		
		#if 0
			//Test if Vecor to string method
		#endif
		
		char * _string = vec3_tostring(&_myvec);
		#ifdef debug
			printf("result vec3 tostring: \"%s\"\n",_string);
		#endif		
		free(_string);
		
		#if 0
			//Test if Vecor additions
		#endif
		
		vec3_t _myvec2 = {1.1f, 1.1f, 1.1f};
		
		vec3_add(&_myvec, &_myvec2);
		
		assert(_myvec.x == 2.1f);
		assert(_myvec.y == 3.1f);
		assert(_myvec.z == 4.1f);
		
		vec3_t * _myvec3 = vec3_add_new(&_myvec, &_myvec2);
		
		//compare with floating point issue (could be realized into string format and compare as strings=>slow) this is enough for us
		assert(_myvec3->x >= 3.199 &&  _myvec3->x <= 3.200001);
		assert(_myvec3->y >= 4.199 &&  _myvec3->y <= 4.200001);
		assert(_myvec3->z >= 5.199 &&  _myvec3->z <= 5.200001);
		
		free(_myvec3);
		
		
		#if 0
			//Test if Vecor difference
		#endif
		
		vec3_t _myvec_sub = {2.0f, 2.0f, 2.0f};
		vec3_t _myvec_sub2 = {1.0f, 1.0f, 1.0f};
		
		vec3_sub(&_myvec_sub, &_myvec_sub2);
		
		assert(_myvec_sub.x == 1.0f);
		assert(_myvec_sub.y == 1.0f);
		assert(_myvec_sub.z == 1.0f);
		
		vec3_t * _myvec3_sub = vec3_sub_new(&_myvec_sub, &_myvec_sub2);
		
		//compare with floating point issue (could be realized into string format and compare as strings=>slow) this is enough for us
		assert(_myvec3_sub->x >= 0.0f &&  _myvec3_sub->x <= 1.0);
		assert(_myvec3_sub->y >= 0.0f &&  _myvec3_sub->y <= 1.0);
		assert(_myvec3_sub->z >= 0.0f &&  _myvec3_sub->z <= 1.0);
		
		free(_myvec3_sub);
		
		#if 0
			//Test if Vecor negation
		#endif
		
		vec3_t _myvec_neg = {1.0f, 2.0f, 3.0f};
		
		vec3_negate(&_myvec_neg);
		
		assert(_myvec_neg.x == -1.0f);
		assert(_myvec_neg.y == -2.0f);
		assert(_myvec_neg.z == -3.0f);
		
		vec3_t * _myvec_neg_new = vec3_negate_new(&_myvec_neg);
		
		assert(_myvec_neg_new->x == 1.0f);
		assert(_myvec_neg_new->y == 2.0f);
		assert(_myvec_neg_new->z == 3.0f);
		
		free(_myvec_neg_new);
		
		#if 0
			//Test Vector copy
		#endif
		
		vec3_t _myvec_cpy = {5.0f, 6.0f, 7.0f};
		
		vec3_t * _copy = vec3_copy_new(&_myvec_cpy);
		
		assert(&_myvec_cpy != _copy);
		assert(_myvec_cpy.x == _copy->x);
		assert(_myvec_cpy.y == _copy->y);
		assert(_myvec_cpy.z == _copy->z);
		
		free(_copy);
		
		#if 0
			//Test Vector length
		#endif
		
		vec3_t _myvec_len = {5.0f, 6.0f, 7.0f};
		float _length = vec3_length(&_myvec_len);
		assert(_length == 10.488088481701515469914535136799f);
		
		#if 0
			//Test Vector multiplications
		#endif
		
		vec3_t _vec_mul = {2.0f, 3.0f, 4.0f};
		vec3_t _vec_mul2 = {2.0f, 3.0f, 4.0f};
		float _factor = 2.0f;
		
		float _skalarproduct = vec3_vec3mul(&_vec_mul, &_vec_mul2);
		assert(_skalarproduct == 29.0f);
		
		vec3_t * _mulres = vec3_mul_new(&_vec_mul, _factor);
		assert(_mulres->x == 4.0f);
		assert(_mulres->y == 6.0f);
		assert(_mulres->z == 8.0f);
		
		free(_mulres);
		
		vec3_mul(&_vec_mul, _factor);
		
		assert(_vec_mul.x == 4.0f);
		assert(_vec_mul.y == 6.0f);
		assert(_vec_mul.z == 8.0f);
		
		#if 0
			//Test Vector normalisation
		#endif
		
		vec3_t _vec_norm = {2.0f, 3.0f, 4.0f};
		vec3_normalize(&_vec_norm);

		assert(_vec_norm.x == 0.37139067635410372629315244769244f);
		assert(_vec_norm.y == 0.55708601453115558943972867153866f);
		assert(_vec_norm.z == 0.74278135270820745258630489538488f);
		
		float _norm_len = vec3_length(&_vec_norm);
		assert(_norm_len == 1.0f);
		
		vec3_t _vec_norm2 = {2.0f, 3.0f, 4.0f};
		vec3_t * _normalized = vec3_normalize_new(&_vec_norm2);
		
		assert(_normalized->x == 0.37139067635410372629315244769244f);
		assert(_normalized->y == 0.55708601453115558943972867153866f);
		assert(_normalized->z == 0.74278135270820745258630489538488f);
		
		_norm_len = vec3_length(_normalized);
		assert(_norm_len == 1.0f);
		free(_normalized);
		#if 0
			//3D Cross product
		#endif
		
		vec3_t v31 = {1.0f, -5.0f, 2.0f};
		vec3_t v32 = {2.0f, 0.0f, 3.0f};
		
		vec3_t * cross = vec3_cross_new(&v31, &v32);
		
		assert(cross->x == -15.0f);
		assert(cross->y == 1.0f);
		assert(cross->z == 10.0f);
		
		free(cross);
		
		vec3_cross(&v31, &v32);
		
		assert(v31.x == -15.0f);
		assert(v31.y == 1.0f);
		assert(v31.z == 10.0f);
		
		#if 0
			//3D Spat product
		#endif
		
		vec3_t spat1 = { 2.0f, 0.0f, 5.0f};
		vec3_t spat2 = { -1.0f, 5.0f, -2.0f};
		vec3_t spat3 = { 2.0f, 1.0f, 2.0f};
		
		float spatvolume = vec3_spat(&spat1, &spat2, &spat3);
		
		assert(spatvolume == -31.0f);
		
		#if 0
			//Test Vector 3D angle
		#endif
		
		vec3_t vec3_angle1 = {0.0f, 1.0f, 0.f};
		vec3_t vec3_angle2 = {1.0f, 0.0f, 0.f};
		
		float _vec3_angle_rad = vec3_angle(&vec3_angle1, &vec3_angle2);
		float _vec3_degree = _vec3_angle_rad * (180 / M_PI);
		assert(_vec3_degree <= 90.0001f && _vec3_degree >= 90.f );
		
		#if 0
			//Test Vector 3D equals
		#endif
		
		vec3_t vec3_eq = {0.0f, 1.0f, 0.f};
		vec3_t vec3_eq1 = {1.0f, 0.0f, 0.f};
		vec3_t vec3_eq2 = {1.0f, 0.0f, 0.f};
		
		assert(!vec3_equals(&vec3_eq, &vec3_eq1));
		assert(vec3_equals(&vec3_eq1, &vec3_eq1));
		assert(vec3_equals(&vec3_eq1, &vec3_eq2));
		
		#if 0
			//Test Vector 3D orthogonality
		#endif
		
		assert(vec3_isorthogonal(&vec3_eq, &vec3_eq1));
		assert(!vec3_isorthogonal(&vec3_eq, &vec3_eq));
		
		#if 0
			//Test Vector 3D crossproduct on same line
		#endif
		
		vec3_t * cross_spec = vec3_cross_new(&v31, &v32);
		vec3_normalize(cross_spec);
		#ifdef debug
			vec3_print(cross_spec);
		#endif	
		
		
		free(cross_spec);
		
		#if 0
			//Test Vector 3D multiple addition and subtraction
		#endif
		
		vec3_t n_result3;
		vec3_t *n_result_new3;
		vec3_t n13 = {0.0f, 1.0f, 1.0f};
		vec3_t n23 = {1.0f, 1.0f, 1.0f};
		vec3_t n33 = {1.0f, 0.0f, 1.0f};
		vec3_t n43 = {0.5f, 0.5f, 1.0f};
		
		n_result3 = *vec3_add_n_dest(&n_result3, 4, &n13, &n23, &n33, &n43);
		
		n_result_new3 = vec3_add_n_new( 4, &n13, &n23, &n33, &n43);
		
		assert(n_result3.x == 2.5f);
		assert(n_result3.y == 2.5f);
		assert(n_result3.z == 4.f);
		
		assert(n_result_new3->x == 2.5f);
		assert(n_result_new3->y == 2.5f);
		assert(n_result_new3->z == 4.f);
		
		free(n_result_new3);
		
		n_result3 = *vec3_sub_n_dest(&n_result3, 4, &n13, &n23, &n33, &n43);
		
		n_result_new3 = vec3_sub_n_new( 4, &n13, &n23, &n33, &n43);
		
		assert(n_result3.x == -2.5f);
		assert(n_result3.y == -2.5f);
		assert(n_result3.z == -4.f);
		
		assert(n_result_new3->x == -2.5f);
		assert(n_result_new3->y == -2.5f);
		assert(n_result_new3->z == -4.f);
		
		free(n_result_new3);
		
		#ifdef debug
			printf("End testing vec3:\n");
		#endif	
	#endif

	return 0;
}