#if 0
/**
	This is a Test programm for vec 2 and 3 implementation.
*/
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "mat.h"

int 
main() {
	#ifdef USE_MAT_2
		#ifdef debug
			printf("Start testing mat2:\n");
		#endif
		
		
		#if 0
			//Test mat2 init
		#endif
		
		mat2_t mat2 = { 1.f, 2.f, 3.f, 4.f};
		
		assert(mat2._11 == 1.0f);
		assert(mat2._12 == 2.0f);
		assert(mat2._21 == 3.0f);
		assert(mat2._22 == 4.0f);
		
		#if 0
			//Test mat2 equals
		#endif
		
		mat2_t mat2_eq = { 1.f, 2.f, 3.f, 4.f};
		mat2_t mat2_eq1 = { 5.f, 6.f, 7.f, 8.f};
		mat2_t mat2_eq2 = { 1.f, 2.f, 3.f, 4.f};
		
		assert(!mat2_equals(&mat2_eq, &mat2_eq1));
		assert(mat2_equals(&mat2_eq, &mat2_eq));
		assert(mat2_equals(&mat2_eq, &mat2_eq2));
		
		#if 0
			//Test if mat2 to string method
		#endif
		
		#ifdef debug
			mat2_print(&mat2);
		#endif
		
		#if 0
			//Test mat2 addition
		#endif
		
		mat2_t mat2_add1 = { 1.f, 2.f, 3.f, 4.f};
		mat2_t mat2_add2 = { 1.f, 2.f, 3.f, 4.f};
		mat2_t mat2_add_result = { 2.f, 4.f, 6.f, 8.f};
		
		mat2_t * _mat2_add_new = mat2_add_new(&mat2_add1, &mat2_add2);
		assert(mat2_equals(_mat2_add_new, &mat2_add_result));
		free(_mat2_add_new);
		
		mat2_add(&mat2_add1, &mat2_add2);
		assert(mat2_equals(&mat2_add1, &mat2_add_result));
	
		
		#if 0
			//Test mat2 sub
		#endif
		
		mat2_t * _mat2_sub_new = mat2_sub_new(&mat2_add1, &mat2_add2);
		assert(mat2_equals(_mat2_sub_new, &mat2_add2));
		free(_mat2_sub_new);
		
		mat2_sub(&mat2_add1, &mat2_add2);
		assert(mat2_equals(&mat2_add1, &mat2_add2));
		
		#if 0
			//Test mat2 copy
		#endif
		
		mat2_t mat2_cpy = { 1.f, 2.f, 3.f, 4.f};
		mat2_t mat2_cpy1 = { 5.f, 6.f, 7.f, 8.f};
		
		mat2_t * mat2_copied = mat2_copy_new(&mat2_cpy);
		assert(mat2_equals(mat2_copied, &mat2_cpy));
		
		free(mat2_copied);
		
		mat2_copy(&mat2_cpy, &mat2_cpy1);
		assert(mat2_equals(&mat2_cpy, &mat2_cpy1));
		
		#if 0
			//Test mat2 mul
		#endif
		
		mat2_t mat2_mul_ = { 1.f, 2.f, 3.f, 4.f};
		mat2_t mat2_mul1 = { 1.f, 2.f, 3.f, 4.f};
		mat2_t mat2_result ={ 7.f, 10.f, 15.f, 22.f};
		
		mat2_t * mat2_muled = mat2_mul_new(&mat2_mul_, &mat2_mul1);
		assert(mat2_equals(mat2_muled, &mat2_result));
		
		free(mat2_muled);
		
		mat2_mul(&mat2_mul_, &mat2_mul1);
		assert(mat2_equals(&mat2_mul_, &mat2_result));
		
		#if 0
			//Test mat2 transponse
		#endif
		
		mat2_t mat2_trans_ = { 1.f, 2.f, 3.f, 4.f};
		mat2_t mat2_trans_result = { 1.f, 3.f, 2.f, 4.f };
		
		mat2_t * mat2_trans_new = mat2_transponse_new(&mat2_trans_);
		
		#ifdef debug
			mat2_print(mat2_trans_new);
			mat2_print(&mat2_trans_result);
		#endif
		
		
		assert(mat2_equals(mat2_trans_new, &mat2_trans_result));
		free(mat2_trans_new);
		
		mat2_transponse(&mat2_trans_);
		assert(mat2_equals(&mat2_trans_, &mat2_trans_result));
		
		#if 0
			//Test mat2 determinant
		#endif
		
		mat2_t mat2_det = {1.f,2.f,3.f,4.f};
		assert(mat2_determinant(&mat2_det) == -2.f);
		
		#if 0
			//Test mat2 inverse
		#endif
		
		mat2_t mat2_inverse_base = {1.f,2.f,3.f,4.f};
		mat2_t mat2_inverse_ = {1.f,2.f,3.f,4.f};
		mat2_t mat2_unity = { 1.f, 0.f, 0.f, 1.f };
		
		mat2_inverse(&mat2_inverse_base);
		mat2_mul(&mat2_inverse_base, &mat2_inverse_);
		assert(mat2_equals(&mat2_inverse_base, &mat2_unity));
		
		mat2_t * mat_inversenew = mat2_inverse_new(&mat2_inverse_);
		mat2_mul(mat_inversenew, &mat2_inverse_);
		
		assert(mat2_equals(mat_inversenew, &mat2_unity));
		
		free(mat_inversenew);
		#ifdef debug
			printf("End testing mat2:\n");
		#endif		
	#endif
	
	#ifdef USE_MAT_3
		#ifdef debug
			printf("Start testing mat3:\n");
		#endif
		
		#if 0
			//Test mat3 init
		#endif
		
		mat3_t mat3 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		
		assert(mat3._11 == 1.0f);
		assert(mat3._12 == 2.0f);
		assert(mat3._13 == 3.0f);
		assert(mat3._21 == 4.0f);
		assert(mat3._22 == 5.0f);
		assert(mat3._23 == 6.0f);
		assert(mat3._31 == 7.0f);
		assert(mat3._32 == 8.0f);
		assert(mat3._33 == 9.0f);

		
		#if 0
			//Test mat3 equals
		#endif
		
		mat3_t mat3_eq = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		mat3_t mat3_eq1 = { 3.f, 3.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		mat3_t mat3_eq2 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		
		assert(!mat3_equals(&mat3_eq, &mat3_eq1));
		assert(mat3_equals(&mat3_eq, &mat3_eq));
		assert(mat3_equals(&mat3_eq, &mat3_eq2));
		
		#if 0
			//Test if mat2 to string method
		#endif
		
		#ifdef debug
			mat3_print(&mat3);
		#endif
		
		#if 0
			//Test mat3 addition
		#endif
		
		mat3_t mat3_add1 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		mat3_t mat3_add2 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		mat3_t mat3_add_result = { 2.f, 4.f, 6.f, 8.f, 10.f, 12.f , 14.f, 16.f, 18.f};
		
		mat3_t * _mat3_add_new = mat3_add_new(&mat3_add1, &mat3_add2);
		assert(mat3_equals(_mat3_add_new, &mat3_add_result));		
		free(_mat3_add_new);
		
		mat3_add(&mat3_add1, &mat3_add2);
		assert(mat3_equals(&mat3_add1, &mat3_add_result));
		
		#if 0
			//Test mat3 sub
		#endif
		
		mat3_t * _mat3_sub_new = mat3_sub_new(&mat3_add1, &mat3_add2);
		assert(mat3_equals(_mat3_sub_new, &mat3_add2));		
		free(_mat3_sub_new);
		
		mat3_sub(&mat3_add1, &mat3_add2);
		assert(mat3_equals(&mat3_add1, &mat3_add2));	
		
		#if 0
			//Test mat3 copy
		#endif
		
		mat3_t mat3_cpy = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		mat3_t mat3_cpy1 = { 3.f, 3.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		
		mat3_t * mat3_copied = mat3_copy_new(&mat3_cpy);
		assert(mat3_equals(mat3_copied, &mat3_cpy));
		
		free(mat3_copied);
		
		mat3_copy(&mat3_cpy, &mat3_cpy1);
		assert(mat3_equals(&mat3_cpy, &mat3_cpy1));
		
		#if 0
			//Test mat3 mul
		#endif
		
		mat3_t mat3_mul_ = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		mat3_t mat3_mul1 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		mat3_t mat3_result ={ 30.f, 36.f, 42.f, 66.f, 81.f, 96.f, 102.f, 126.f, 150.f};
		
		mat3_t * mat3_muled = mat3_mul_new(&mat3_mul_, &mat3_mul1);
		assert(mat3_equals(mat3_muled, &mat3_result));
		
		free(mat3_muled);
		
		mat3_mul(&mat3_mul_, &mat3_mul1);
		assert(mat3_equals(&mat3_mul_, &mat3_result));
		
		#if 0
			//Test mat3 transponse
		#endif
		
		mat3_t mat3_trans_ = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
		mat3_t mat3_trans_result = { 1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f};
		
		mat3_t * mat3_trans_new = mat3_transponse_new(&mat3_trans_);

		#ifdef debug
			mat3_print(mat3_trans_new);
			mat3_print(&mat3_trans_result);
		#endif
		
		assert(mat3_equals(mat3_trans_new, &mat3_trans_result));
		free(mat3_trans_new);
		
		mat3_transponse(&mat3_trans_);
		assert(mat3_equals(&mat3_trans_, &mat3_trans_result));
		
		#if 0
			//Test mat3 determinant
		#endif
		
		mat3_t mat3_det = {11.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f};
		assert(mat3_determinant(&mat3_det) == -30.f);
		
		#if 0
			//Test mat3 inverse
		#endif
		
		mat3_t mat3_inverse_base = {1.f, 2.f, 0.f, 2.f, 4.f, 1.f, 2.f, 1.f, 0.f};
		mat3_t mat3_inverse_ = {1.f, 2.f, 0.f, 2.f, 4.f, 1.f, 2.f, 1.f, 0.f};
		mat3_t mat3_unity = { 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f};
		
		mat3_inverse(&mat3_inverse_base);
		mat3_mul(&mat3_inverse_base, &mat3_inverse_);
		assert(mat3_equals(&mat3_inverse_base, &mat3_unity));
		
		mat3_t * mat3_inversenew = mat3_inverse_new(&mat3_inverse_);
		mat3_mul(mat3_inversenew, &mat3_inverse_);
		
		assert(mat3_equals(mat3_inversenew, &mat3_unity));
		
		free(mat3_inversenew);
		
		#ifdef debug
			printf("End testing mat3:\n");
		#endif
	#endif
	
	#ifdef USE_MAT_4
		#ifdef debug
			printf("Start testing mat4:\n");
		#endif
		
		#if 0
			//Test mat4 init
		#endif
		
		mat4_t mat4 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		
		assert(mat4._11 == 1.0f);
		assert(mat4._12 == 2.0f);
		assert(mat4._13 == 3.0f);
		assert(mat4._14 == 4.0f);
		assert(mat4._21 == 5.0f);
		assert(mat4._22 == 6.0f);
		assert(mat4._23 == 7.0f);
		assert(mat4._24 == 8.0f);
		assert(mat4._31 == 9.0f);
		assert(mat4._32 == 10.0f);
		assert(mat4._33 == 11.0f);
		assert(mat4._34 == 12.0f);
		assert(mat4._41 == 13.0f);
		assert(mat4._42 == 14.0f);
		assert(mat4._43 == 15.0f);
		assert(mat4._44 == 16.0f);

		#if 0
			//Test mat4 equals
		#endif
		
		mat4_t mat4_eq = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		mat4_t mat4_eq1 = { 3.f, 3.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		mat4_t mat4_eq2 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		
		assert(!mat4_equals(&mat4_eq, &mat4_eq1));
		assert(mat4_equals(&mat4_eq, &mat4_eq));
		assert(mat4_equals(&mat4_eq, &mat4_eq2));
		
		#if 0
			//Test if mat4 to string method
		#endif
		
		#ifdef debug
			mat4_print(&mat4);
		#endif
		
		#if 0
			//Test mat4 addition
		#endif
		
		mat4_t mat4_add1 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		mat4_t mat4_add2 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		mat4_t mat4_add_result = { 2.f, 4.f, 6.f, 8.f, 10.f, 12.f , 14.f, 16.f, 18.f, 20.f, 22.f,24.f,26.f,28.f,30.f,32.f};
		
		mat4_t * _mat4_add_new = mat4_add_new(&mat4_add1, &mat4_add2);
		assert(mat4_equals(_mat4_add_new, &mat4_add_result));
		free(_mat4_add_new);
		
		mat4_add(&mat4_add1, &mat4_add2);
		assert(mat4_equals(&mat4_add1, &mat4_add_result));
		
		#if 0
			//Test mat4 sub
		#endif
		
		mat4_t * _mat4_sub_new = mat4_sub_new(&mat4_add1, &mat4_add2);
		assert(mat4_equals(_mat4_sub_new, &mat4_add2));
		free(_mat4_sub_new);
		
		mat4_sub(&mat4_add1, &mat4_add2);
		assert(mat4_equals(&mat4_add1, &mat4_add2));
		
		#if 0
			//Test mat4 copy
		#endif
		
		mat4_t mat4_cpy = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		mat4_t mat4_cpy1 = { 2.f, 3.f, 4.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		
		mat4_t * mat4_copied = mat4_copy_new(&mat4_cpy);
		assert(mat4_equals(mat4_copied, &mat4_cpy));
		
		free(mat4_copied);
		
		mat4_copy(&mat4_cpy, &mat4_cpy1);
		assert(mat4_equals(&mat4_cpy, &mat4_cpy1));
		
		#if 0
			//Test mat4 mul
		#endif
		
		mat4_t mat4_mul_ = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		mat4_t mat4_mul1 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		mat4_t mat4_result = { 90.f, 100.f,110.f, 120.f, 202.f, 228.f, 254.f , 280.f, 314.f, 356.f, 398.f, 440.f, 426.f, 484.f, 542.f, 600.f};
		
		mat4_t * mat4_muled = mat4_mul_new(&mat4_mul_, &mat4_mul1);
		assert(mat4_equals(mat4_muled, &mat4_result));
		
		free(mat4_muled);
		
		mat4_mul(&mat4_mul_, &mat4_mul1);
		assert(mat4_equals(&mat4_mul_, &mat4_result));
		
		#if 0
			//Test mat4 transponse
		#endif
		
		mat4_t mat4_trans_ = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		mat4_t mat4_trans_result = { 1.f, 5.f, 9.f, 13.f, 2.f, 6.f , 10.f, 14.f, 3.f, 7.f, 11.f, 15.f, 4.f, 8.f, 12.f, 16.f};
		
		mat4_t * mat4_trans_new = mat4_transponse_new(&mat4_trans_);
		
		#ifdef debug
			mat4_print(mat4_trans_new);
			mat4_print(&mat4_trans_result);
		#endif
		
		assert(mat4_equals(mat4_trans_new, &mat4_trans_result));
		free(mat4_trans_new);
		
		mat4_transponse(&mat4_trans_);
		assert(mat4_equals(&mat4_trans_, &mat4_trans_result));
		
		
		#if 0
			//Test mat4 determinant
		#endif
		
		mat4_t mat4_det = { 5.f, 0.f, 3.f, -1.f, 3.f, 0.f , 0.f, 4.f, -1.f, 2.f, 4.f, -2.f, 1.f, 0.f, 0.f, 5.f};
		assert(mat4_determinant(&mat4_det) == 66.f);
		
		#if 0
			//Test mat4 inverse
		#endif
		
		mat4_t mat4_inverse_base = {1.f, 2.f, 3.f, 4.f, -1.f, 2.f, 0.f, 5.f, 0.f, 4.f, -2.f, 6.f, 2.f, 4.f, 0.f, 6.f };
		mat4_t mat4_inverse_ = {1.f, 2.f, 3.f, 4.f, -1.f, 2.f, 0.f, 5.f, 0.f, 4.f, -2.f, 6.f, 2.f, 4.f, 0.f, 6.f };
		mat4_t mat4_unity = { 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f};
		
		mat4_inverse(&mat4_inverse_base);
		mat4_mul(&mat4_inverse_base, &mat4_inverse_);
		assert(mat4_equals(&mat4_inverse_base, &mat4_unity));
		
		mat4_t * mat4_inversenew = mat4_inverse_new(&mat4_inverse_);
		mat4_mul(mat4_inversenew, &mat4_inverse_);

		assert(mat4_equals(mat4_inversenew, &mat4_unity));
		
		free(mat4_inversenew);
		
		#ifdef debug
			printf("End testing mat4:\n");
		#endif
	#endif
	
	return 0;
}