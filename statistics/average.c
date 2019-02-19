#include "average.h"

float 
middle_arithmetic(const float x1, const float x2, const float x3, const float x4){
	return (x1 + x2 + x3 + x4)*0.25f;
}

float 
middle_arithmetic2(const float x1, const float x2){
	return (x1 + x2)*0.5f;
}

float 
middle_harmonic(const float x1, const float x2, const float x3, const float x4){
	return 4.f/(1./x1 + 1./x2 + 1.f/x3 + 1./x4);
}

float 
middle_harmonic2(const float x1, const float x2){
	return 2.f/(1./x1 + 1./x2);
}

float 
middle_quantil(const float x1, const float x2, const float x3, const float x4){
	float values[] = { x1, x2, x3, x4 };
	
	qsort(values, 4, sizeof(float), compare_floats);
	
	return (values[0] + values[2])/2.f;
}

float 
middle_median(const float x1, const float x2, const float x3, const float x4){
	float values[] = { x1, x2, x3, x4 };
	
	qsort(values, 4, sizeof(float), compare_floats);
	
	return (values[1] + values[2])/2.f;
}

float 
middle_quad(const float x1, const float x2, const float x3, const float x4){
	return sqrtf(((x1*x1)+(x2*x2)+(x3*x3)+(x4*x4))*0.25f);
}

float 
middle_quad2(const float x1, const float x2){
	return sqrtf(((x1*x1)+(x2*x2))*0.5f);
}

float 
middle_cubic(const float x1, const float x2, const float x3, const float x4){
	return cbrtf(((x1*x1*x1)+(x2*x2*x2)+(x3*x3*x3)+(x4*x4*x4))*0.25f);
}

float 
middle_cubic2(const float x1, const float x2){
	return cbrtf(((x1*x1*x1)+(x2*x2*x2))*0.5f);
}

float 
middle_geometric(const float x1, const float x2, const float x3, const float x4){
	return powf(x1*x2*x3*x4,0.25f);
}

float 
middle_geometric2(const float x1, const float x2){
	return powf(x1*x2,0.5f);
}

float 
middle_hoelder(const float x1, const float x2, const float x3, const float x4){
	return powf(((x1*x1*x1*x1)+(x2*x2*x2*x2)+(x3*x3*x3*x3)+(x4*x4*x4*x4))*0.25f, 0.25f);
}

float 
middle_hoelder2(const float x1, const float x2){
	return powf(((x1*x1)+(x2*x2))*0.5f, 0.5f);
}