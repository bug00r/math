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
		
		Mat2 mat2 = { 1.f, 2.f, 3.f, 4.f};
		
		assert(mat2._11 == 1.0f);
		assert(mat2._12 == 2.0f);
		assert(mat2._21 == 3.0f);
		assert(mat2._22 == 4.0f);
		
		#if 0
			//Test mat2 equals
		#endif
		
		Mat2 mat2_eq = { 1.f, 2.f, 3.f, 4.f};
		Mat2 mat2_eq1 = { 5.f, 6.f, 7.f, 8.f};
		Mat2 mat2_eq2 = { 1.f, 2.f, 3.f, 4.f};
		
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
		
		Mat2 mat2_add1 = { 1.f, 2.f, 3.f, 4.f};
		Mat2 mat2_add2 = { 1.f, 2.f, 3.f, 4.f};
		Mat2 mat2_add_result = { 2.f, 4.f, 6.f, 8.f};
		
		Mat2 * _mat2_add_new = mat2_add_new(&mat2_add1, &mat2_add2);
		assert(mat2_equals(_mat2_add_new, &mat2_add_result));
		free(_mat2_add_new);
		
		mat2_add(&mat2_add1, &mat2_add2);
		assert(mat2_equals(&mat2_add1, &mat2_add_result));
	
		
		#if 0
			//Test mat2 sub
		#endif
		
		Mat2 * _mat2_sub_new = mat2_sub_new(&mat2_add1, &mat2_add2);
		assert(mat2_equals(_mat2_sub_new, &mat2_add2));
		free(_mat2_sub_new);
		
		mat2_sub(&mat2_add1, &mat2_add2);
		assert(mat2_equals(&mat2_add1, &mat2_add2));
		
		#if 0
			//Test mat2 copy
		#endif
		
		Mat2 mat2_cpy = { 1.f, 2.f, 3.f, 4.f};
		Mat2 mat2_cpy1 = { 5.f, 6.f, 7.f, 8.f};
		
		Mat2 * mat2_copied = mat2_copy_new(&mat2_cpy);
		assert(mat2_equals(mat2_copied, &mat2_cpy));
		
		free(mat2_copied);
		
		mat2_copy(&mat2_cpy, &mat2_cpy1);
		assert(mat2_equals(&mat2_cpy, &mat2_cpy1));
		
		#if 0
			//Test mat2 mul
		#endif
		
		Mat2 mat2_mul_ = { 1.f, 2.f, 3.f, 4.f};
		Mat2 mat2_mul1 = { 1.f, 2.f, 3.f, 4.f};
		Mat2 mat2_result ={ 7.f, 10.f, 15.f, 22.f};
		
		Mat2 * mat2_muled = mat2_mul_new(&mat2_mul_, &mat2_mul1);
		assert(mat2_equals(mat2_muled, &mat2_result));
		
		free(mat2_muled);
		
		mat2_mul(&mat2_mul_, &mat2_mul1);
		assert(mat2_equals(&mat2_mul_, &mat2_result));
		
		#if 0
			//Test mat2 transponse
		#endif
		
		Mat2 Mat2rans_ = { 1.f, 2.f, 3.f, 4.f};
		Mat2 Mat2rans_result = { 1.f, 3.f, 2.f, 4.f };
		
		Mat2 * Mat2rans_new = Mat2ransponse_new(&Mat2rans_);
		
		#ifdef debug
			mat2_print(Mat2rans_new);
			mat2_print(&Mat2rans_result);
		#endif
		
		
		assert(mat2_equals(Mat2rans_new, &Mat2rans_result));
		free(Mat2rans_new);
		
		Mat2ransponse(&Mat2rans_);
		assert(mat2_equals(&Mat2rans_, &Mat2rans_result));
		
		#if 0
			//Test mat2 determinant
		#endif
		
		Mat2 mat2_det = {1.f,2.f,3.f,4.f};
		assert(mat2_determinant(&mat2_det) == -2.f);
		
		#if 0
			//Test mat2 inverse
		#endif
		
		Mat2 mat2_inverse_base = {1.f,2.f,3.f,4.f};
		Mat2 mat2_inverse_ = {1.f,2.f,3.f,4.f};
		Mat2 mat2_unity = { 1.f, 0.f, 0.f, 1.f };
		
		mat2_inverse(&mat2_inverse_base);
		mat2_mul(&mat2_inverse_base, &mat2_inverse_);
		assert(mat2_equals(&mat2_inverse_base, &mat2_unity));
		
		Mat2 * mat_inversenew = mat2_inverse_new(&mat2_inverse_);
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
		
		Mat3 mat3 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		
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
		
		Mat3 mat3_eq = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		Mat3 mat3_eq1 = { 3.f, 3.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		Mat3 mat3_eq2 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		
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
		
		Mat3 mat3_add1 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		Mat3 mat3_add2 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		Mat3 mat3_add_result = { 2.f, 4.f, 6.f, 8.f, 10.f, 12.f , 14.f, 16.f, 18.f};
		
		Mat3 * _mat3_add_new = mat3_add_new(&mat3_add1, &mat3_add2);
		assert(mat3_equals(_mat3_add_new, &mat3_add_result));		
		free(_mat3_add_new);
		
		mat3_add(&mat3_add1, &mat3_add2);
		assert(mat3_equals(&mat3_add1, &mat3_add_result));
		
		#if 0
			//Test mat3 sub
		#endif
		
		Mat3 * _mat3_sub_new = mat3_sub_new(&mat3_add1, &mat3_add2);
		assert(mat3_equals(_mat3_sub_new, &mat3_add2));		
		free(_mat3_sub_new);
		
		mat3_sub(&mat3_add1, &mat3_add2);
		assert(mat3_equals(&mat3_add1, &mat3_add2));	
		
		#if 0
			//Test mat3 copy
		#endif
		
		Mat3 mat3_cpy = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		Mat3 mat3_cpy1 = { 3.f, 3.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		
		Mat3 * mat3_copied = mat3_copy_new(&mat3_cpy);
		assert(mat3_equals(mat3_copied, &mat3_cpy));
		
		free(mat3_copied);
		
		mat3_copy(&mat3_cpy, &mat3_cpy1);
		assert(mat3_equals(&mat3_cpy, &mat3_cpy1));
		
		#if 0
			//Test mat3 mul
		#endif
		
		Mat3 mat3_mul_ = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		Mat3 mat3_mul1 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f};
		Mat3 mat3_result ={ 30.f, 36.f, 42.f, 66.f, 81.f, 96.f, 102.f, 126.f, 150.f};
		
		Mat3 * mat3_muled = mat3_mul_new(&mat3_mul_, &mat3_mul1);
		assert(mat3_equals(mat3_muled, &mat3_result));
		
		free(mat3_muled);
		
		mat3_mul(&mat3_mul_, &mat3_mul1);
		assert(mat3_equals(&mat3_mul_, &mat3_result));
		
		#if 0
			//Test mat3 transponse
		#endif
		
		Mat3 Mat3rans_ = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
		Mat3 Mat3rans_result = { 1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f};
		
		Mat3 * Mat3rans_new = Mat3ransponse_new(&Mat3rans_);

		#ifdef debug
			mat3_print(Mat3rans_new);
			mat3_print(&Mat3rans_result);
		#endif
		
		assert(mat3_equals(Mat3rans_new, &Mat3rans_result));
		free(Mat3rans_new);
		
		Mat3ransponse(&Mat3rans_);
		assert(mat3_equals(&Mat3rans_, &Mat3rans_result));
		
		#if 0
			//Test mat3 determinant
		#endif
		
		Mat3 mat3_det = {11.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f};
		assert(mat3_determinant(&mat3_det) == -30.f);
		
		#if 0
			//Test mat3 inverse
		#endif
		
		Mat3 mat3_inverse_base = {1.f, 2.f, 0.f, 2.f, 4.f, 1.f, 2.f, 1.f, 0.f};
		Mat3 mat3_inverse_ = {1.f, 2.f, 0.f, 2.f, 4.f, 1.f, 2.f, 1.f, 0.f};
		Mat3 mat3_unity = { 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f};
		
		mat3_inverse(&mat3_inverse_base);
		mat3_mul(&mat3_inverse_base, &mat3_inverse_);
		assert(mat3_equals(&mat3_inverse_base, &mat3_unity));
		
		Mat3 * mat3_inversenew = mat3_inverse_new(&mat3_inverse_);
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
		
		Mat4 mat4 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		
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
		
		Mat4 mat4_eq = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		Mat4 mat4_eq1 = { 3.f, 3.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		Mat4 mat4_eq2 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		
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
		
		Mat4 mat4_add1 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		Mat4 mat4_add2 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		Mat4 mat4_add_result = { 2.f, 4.f, 6.f, 8.f, 10.f, 12.f , 14.f, 16.f, 18.f, 20.f, 22.f,24.f,26.f,28.f,30.f,32.f};
		
		Mat4 * _mat4_add_new = mat4_add_new(&mat4_add1, &mat4_add2);
		assert(mat4_equals(_mat4_add_new, &mat4_add_result));
		free(_mat4_add_new);
		
		mat4_add(&mat4_add1, &mat4_add2);
		assert(mat4_equals(&mat4_add1, &mat4_add_result));
		
		#if 0
			//Test mat4 sub
		#endif
		
		Mat4 * _mat4_sub_new = mat4_sub_new(&mat4_add1, &mat4_add2);
		assert(mat4_equals(_mat4_sub_new, &mat4_add2));
		free(_mat4_sub_new);
		
		mat4_sub(&mat4_add1, &mat4_add2);
		assert(mat4_equals(&mat4_add1, &mat4_add2));
		
		#if 0
			//Test mat4 copy
		#endif
		
		Mat4 mat4_cpy = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		Mat4 mat4_cpy1 = { 2.f, 3.f, 4.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		
		Mat4 * mat4_copied = mat4_copy_new(&mat4_cpy);
		assert(mat4_equals(mat4_copied, &mat4_cpy));
		
		free(mat4_copied);
		
		mat4_copy(&mat4_cpy, &mat4_cpy1);
		assert(mat4_equals(&mat4_cpy, &mat4_cpy1));
		
		#if 0
			//Test mat4 mul
		#endif
		
		Mat4 mat4_mul_ = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		Mat4 mat4_mul1 = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		Mat4 mat4_result = { 90.f, 100.f,110.f, 120.f, 202.f, 228.f, 254.f , 280.f, 314.f, 356.f, 398.f, 440.f, 426.f, 484.f, 542.f, 600.f};
		
		Mat4 * mat4_muled = mat4_mul_new(&mat4_mul_, &mat4_mul1);
		assert(mat4_equals(mat4_muled, &mat4_result));
		
		free(mat4_muled);
		
		mat4_mul(&mat4_mul_, &mat4_mul1);
		assert(mat4_equals(&mat4_mul_, &mat4_result));
		
		#if 0
			//Test mat4 transponse
		#endif
		
		Mat4 Mat4rans_ = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f , 7.f, 8.f, 9.f, 10.f, 11.f,12.f,13.f,14.f,15.f,16.f};
		Mat4 Mat4rans_result = { 1.f, 5.f, 9.f, 13.f, 2.f, 6.f , 10.f, 14.f, 3.f, 7.f, 11.f, 15.f, 4.f, 8.f, 12.f, 16.f};
		
		Mat4 * Mat4rans_new = Mat4ransponse_new(&Mat4rans_);
		
		#ifdef debug
			mat4_print(Mat4rans_new);
			mat4_print(&Mat4rans_result);
		#endif
		
		assert(mat4_equals(Mat4rans_new, &Mat4rans_result));
		free(Mat4rans_new);
		
		Mat4ransponse(&Mat4rans_);
		assert(mat4_equals(&Mat4rans_, &Mat4rans_result));
		
		
		#if 0
			//Test mat4 determinant
		#endif
		
		Mat4 mat4_det = { 5.f, 0.f, 3.f, -1.f, 3.f, 0.f , 0.f, 4.f, -1.f, 2.f, 4.f, -2.f, 1.f, 0.f, 0.f, 5.f};
		assert(mat4_determinant(&mat4_det) == 66.f);
		
		#if 0
			//Test mat4 inverse
		#endif
		
		Mat4 mat4_inverse_base = {1.f, 2.f, 3.f, 4.f, -1.f, 2.f, 0.f, 5.f, 0.f, 4.f, -2.f, 6.f, 2.f, 4.f, 0.f, 6.f };
		Mat4 mat4_inverse_ = {1.f, 2.f, 3.f, 4.f, -1.f, 2.f, 0.f, 5.f, 0.f, 4.f, -2.f, 6.f, 2.f, 4.f, 0.f, 6.f };
		Mat4 mat4_unity = { 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f};
		
		mat4_inverse(&mat4_inverse_base);
		mat4_mul(&mat4_inverse_base, &mat4_inverse_);
		assert(mat4_equals(&mat4_inverse_base, &mat4_unity));
		
		Mat4 * mat4_inversenew = mat4_inverse_new(&mat4_inverse_);
		mat4_mul(mat4_inversenew, &mat4_inverse_);

		assert(mat4_equals(mat4_inversenew, &mat4_unity));
		
		free(mat4_inversenew);
		
		#ifdef debug
			printf("End testing mat4:\n");
		#endif
	#endif
	
	return 0;
}