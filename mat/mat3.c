const size_t mat3_size = sizeof(Mat3);

float 
mat3_determinant(const Mat3 *  m){
	return (m->_11*m->_22*m->_33) +
		   (m->_12*m->_23*m->_31) + 
		   (m->_13*m->_21*m->_32) -
		   (m->_13*m->_22*m->_31) -
		   (m->_12*m->_21*m->_33) -
		   (m->_11*m->_23*m->_32);
}

bool 
mat3_equals( const Mat3 *  m, const Mat3 *  m2){
	return (m == m2) || 
		   (m->_11 == m2->_11 &&
			m->_12 == m2->_12 &&
			m->_13 == m2->_13 &&
			m->_21 == m2->_21 &&
			m->_22 == m2->_22 &&
			m->_23 == m2->_23 &&
			m->_31 == m2->_31 &&
			m->_32 == m2->_32 &&
			m->_33 == m2->_33);
}

void 
Mat3ransponse( Mat3 *  m){
	float temp = m->_21;
	m->_21 = m->_12;
	m->_12 = temp;
	temp = m->_31;
	m->_31 = m->_13;
	m->_13 = temp;
	temp = m->_32;
	m->_32 = m->_23;
	m->_23 = temp;
}


Mat3 * 
Mat3ransponse_new( const Mat3 * m){
	Mat3 *newmat = mat3_copy_new(m);
	Mat3ransponse(newmat);
	return newmat;
}

void
mat3_copy( Mat3 *  m, const Mat3 *  m2){
	m->_11 = m2->_11;
	m->_12 = m2->_12;
	m->_13 = m2->_13;
	m->_21 = m2->_21;
	m->_22 = m2->_22;
	m->_23 = m2->_23;
	m->_31 = m2->_31;
	m->_32 = m2->_32;
	m->_33 = m2->_33;
}

Mat3 * 
mat3_copy_new( const Mat3 *  m){
	Mat3 *newmat = malloc(mat3_size);
	mat3_copy(newmat, m);
	return newmat;
}

void
mat3_print( const Mat3 *   m){
	#if 0
		//method cuts to stirng...must improve function for morze big numbers
	#endif
	printf("\n| %f %f %f |\n| %f %f %f |\n| %f %f %f |\n", m->_11, m->_12, m->_13, 
															m->_21, m->_22, m->_23, 
															m->_31, m->_32, m->_33);
}

void 
mat3_add( Mat3 *   m, const Mat3 *   m2){
	m->_11 += m2->_11;
	m->_12 += m2->_12;
	m->_13 += m2->_13;
	m->_21 += m2->_21;
	m->_22 += m2->_22;
	m->_23 += m2->_23;
	m->_31 += m2->_31;
	m->_32 += m2->_32;
	m->_33 += m2->_33;
}

Mat3 * 
mat3_add_new( const Mat3 *   m, const Mat3 *   m2){
	Mat3 *newmat = malloc(mat3_size);
	newmat->_11 = m->_11 + m2->_11;
	newmat->_12 = m->_12 + m2->_12;
	newmat->_13 = m->_13 + m2->_13;
	newmat->_21 = m->_21 + m2->_21;
	newmat->_22 = m->_22 + m2->_22;
	newmat->_23 = m->_23 + m2->_23;
	newmat->_31 = m->_31 + m2->_31;
	newmat->_32 = m->_32 + m2->_32;
	newmat->_33 = m->_33 + m2->_33;
	return newmat;
}

void 
mat3_sub( Mat3 *   m, const Mat3 *   m2){
	m->_11 -= m2->_11;
	m->_12 -= m2->_12;
	m->_13 -= m2->_13;
	m->_21 -= m2->_21;
	m->_22 -= m2->_22;
	m->_23 -= m2->_23;
	m->_31 -= m2->_31;
	m->_32 -= m2->_32;
	m->_33 -= m2->_33;
}

Mat3 * 
mat3_sub_new( const Mat3 *   m, const Mat3 *   m2){
	Mat3 *newmat = malloc(mat3_size);
	newmat->_11 = m->_11 - m2->_11;
	newmat->_12 = m->_12 - m2->_12;
	newmat->_13 = m->_13 - m2->_13;
	newmat->_21 = m->_21 - m2->_21;
	newmat->_22 = m->_22 - m2->_22;
	newmat->_23 = m->_23 - m2->_23;
	newmat->_31 = m->_31 - m2->_31;
	newmat->_32 = m->_32 - m2->_32;
	newmat->_33 = m->_33 - m2->_33;
	return newmat;
}

void 
mat3_mul( Mat3 *   m, const Mat3 *   m2){
	Mat3 temp = {
		(m->_11 * m2->_11) + (m->_12 * m2->_21) + (m->_13 * m2->_31),
		(m->_11 * m2->_12) + (m->_12 * m2->_22) + (m->_13 * m2->_32),
		(m->_11 * m2->_13) + (m->_12 * m2->_23) + (m->_13 * m2->_33),
		(m->_21 * m2->_11) + (m->_22 * m2->_21) + (m->_23 * m2->_31),
		(m->_21 * m2->_12) + (m->_22 * m2->_22) + (m->_23 * m2->_32),
		(m->_21 * m2->_13) + (m->_22 * m2->_23) + (m->_23 * m2->_33),
		(m->_31 * m2->_11) + (m->_32 * m2->_21) + (m->_33 * m2->_31),
		(m->_31 * m2->_12) + (m->_32 * m2->_22) + (m->_33 * m2->_32),
		(m->_31 * m2->_13) + (m->_32 * m2->_23) + (m->_33 * m2->_33)
	};
	mat3_copy(m, &temp);
}

Mat3 * 
mat3_mul_new( const Mat3 *   m, const Mat3 *   m2){
	Mat3 *newmat = malloc(mat3_size);
	newmat->_11 = (m->_11 * m2->_11) + (m->_12 * m2->_21) + (m->_13 * m2->_31);
	newmat->_12 = (m->_11 * m2->_12) + (m->_12 * m2->_22) + (m->_13 * m2->_32);
	newmat->_13 = (m->_11 * m2->_13) + (m->_12 * m2->_23) + (m->_13 * m2->_33);
	newmat->_21 = (m->_21 * m2->_11) + (m->_22 * m2->_21) + (m->_23 * m2->_31);
	newmat->_22 = (m->_21 * m2->_12) + (m->_22 * m2->_22) + (m->_23 * m2->_32);
	newmat->_23 = (m->_21 * m2->_13) + (m->_22 * m2->_23) + (m->_23 * m2->_33);
	newmat->_31 = (m->_31 * m2->_11) + (m->_32 * m2->_21) + (m->_33 * m2->_31);
	newmat->_32 = (m->_31 * m2->_12) + (m->_32 * m2->_22) + (m->_33 * m2->_32);
	newmat->_33 = (m->_31 * m2->_13) + (m->_32 * m2->_23) + (m->_33 * m2->_33);
	return newmat;
}

Mat3 * 
mat3_mul_dest(Mat3 * dest, const Mat3 *   m, const Mat3 *   m2){
	Mat3 *newmat = dest;
	newmat->_11 = (m->_11 * m2->_11) + (m->_12 * m2->_21) + (m->_13 * m2->_31);
	newmat->_12 = (m->_11 * m2->_12) + (m->_12 * m2->_22) + (m->_13 * m2->_32);
	newmat->_13 = (m->_11 * m2->_13) + (m->_12 * m2->_23) + (m->_13 * m2->_33);
	newmat->_21 = (m->_21 * m2->_11) + (m->_22 * m2->_21) + (m->_23 * m2->_31);
	newmat->_22 = (m->_21 * m2->_12) + (m->_22 * m2->_22) + (m->_23 * m2->_32);
	newmat->_23 = (m->_21 * m2->_13) + (m->_22 * m2->_23) + (m->_23 * m2->_33);
	newmat->_31 = (m->_31 * m2->_11) + (m->_32 * m2->_21) + (m->_33 * m2->_31);
	newmat->_32 = (m->_31 * m2->_12) + (m->_32 * m2->_22) + (m->_33 * m2->_32);
	newmat->_33 = (m->_31 * m2->_13) + (m->_32 * m2->_23) + (m->_33 * m2->_33);
	return dest;
}

void 
mat3_mul_skalar( Mat3 *   m, const float skalar){
	m->_11 *= skalar;
	m->_12 *= skalar;
	m->_13 *= skalar;
	m->_21 *= skalar;
	m->_22 *= skalar;
	m->_23 *= skalar;
	m->_31 *= skalar;
	m->_32 *= skalar;
	m->_33 *= skalar;
}

Mat3 * 
mat3_mul_skalar_new( const Mat3 *   m, const float skalar) {
	Mat3 *newmat = malloc(mat3_size);
	mat3_copy(newmat, m);
	mat3_mul_skalar(newmat, skalar);
	return newmat;
}

void 
mat3_inverse( Mat3 *  m){
	Mat2 temp = {0.f, 0.f, 0.f, 0.f};
	Mat3 * cof_mat3 = malloc(mat3_size);
	temp = (Mat2) { m->_22, m->_23, m->_32, m->_33};
	cof_mat3->_11 = mat2_determinant(&temp);
	temp = (Mat2) { m->_21, m->_23, m->_31, m->_33};
	cof_mat3->_12 = -mat2_determinant(&temp);
	temp = (Mat2) { m->_21, m->_22, m->_31, m->_32};
	cof_mat3->_13 = mat2_determinant(&temp);
	
	temp = (Mat2) { m->_12, m->_13, m->_32, m->_33};
	cof_mat3->_21 = -mat2_determinant(&temp);
	temp = (Mat2) { m->_11, m->_13, m->_31, m->_33};
	cof_mat3->_22 = mat2_determinant(&temp);
	temp = (Mat2) { m->_11, m->_12, m->_31, m->_32};
	cof_mat3->_23 = -mat2_determinant(&temp);
	
	temp = (Mat2) { m->_12, m->_13, m->_22, m->_23};
	cof_mat3->_31 = mat2_determinant(&temp);
	temp = (Mat2) { m->_11, m->_13, m->_21, m->_23};
	cof_mat3->_32 = -mat2_determinant(&temp);
	temp = (Mat2) { m->_11, m->_12, m->_21, m->_22};
	cof_mat3->_33 = mat2_determinant(&temp);
	
	Mat3ransponse(cof_mat3);
	mat3_mul_skalar(cof_mat3 , 1.f/mat3_determinant(m));
	mat3_copy(m, cof_mat3);
	free(cof_mat3);
}

void mat3_inverse_dest( Mat3 *   dest, const Mat3 *   m) {
	Mat2 temp = {0.f, 0.f, 0.f, 0.f};
	temp = (Mat2) { m->_22, m->_23, m->_32, m->_33};
	dest->_11 = mat2_determinant(&temp);
	temp = (Mat2) { m->_21, m->_23, m->_31, m->_33};
	dest->_12 = -mat2_determinant(&temp);
	temp = (Mat2) { m->_21, m->_22, m->_31, m->_32};
	dest->_13 = mat2_determinant(&temp);
	
	temp = (Mat2) { m->_12, m->_13, m->_32, m->_33};
	dest->_21 = -mat2_determinant(&temp);
	temp = (Mat2) { m->_11, m->_13, m->_31, m->_33};
	dest->_22 = mat2_determinant(&temp);
	temp = (Mat2) { m->_11, m->_12, m->_31, m->_32};
	dest->_23 = -mat2_determinant(&temp);
	
	temp = (Mat2) { m->_12, m->_13, m->_22, m->_23};
	dest->_31 = mat2_determinant(&temp);
	temp = (Mat2) { m->_11, m->_13, m->_21, m->_23};
	dest->_32 = -mat2_determinant(&temp);
	temp = (Mat2) { m->_11, m->_12, m->_21, m->_22};
	dest->_33 = mat2_determinant(&temp);
	Mat3ransponse(dest);
	mat3_mul_skalar(dest , 1.f/mat3_determinant(m));
}

Mat3 * 
mat3_inverse_new( const Mat3 *   m){
	Mat2 temp = {0.f, 0.f, 0.f, 0.f};
	Mat3 * newmat = malloc(mat3_size);
	temp = (Mat2) { m->_22, m->_23, m->_32, m->_33};
	newmat->_11 = mat2_determinant(&temp);
	temp = (Mat2) { m->_21, m->_23, m->_31, m->_33};
	newmat->_12 = -mat2_determinant(&temp);
	temp = (Mat2) { m->_21, m->_22, m->_31, m->_32};
	newmat->_13 = mat2_determinant(&temp);
	
	temp = (Mat2) { m->_12, m->_13, m->_32, m->_33};
	newmat->_21 = -mat2_determinant(&temp);
	temp = (Mat2) { m->_11, m->_13, m->_31, m->_33};
	newmat->_22 = mat2_determinant(&temp);
	temp = (Mat2) { m->_11, m->_12, m->_31, m->_32};
	newmat->_23 = -mat2_determinant(&temp);
	
	temp = (Mat2) { m->_12, m->_13, m->_22, m->_23};
	newmat->_31 = mat2_determinant(&temp);
	temp = (Mat2) { m->_11, m->_13, m->_21, m->_23};
	newmat->_32 = -mat2_determinant(&temp);
	temp = (Mat2) { m->_11, m->_12, m->_21, m->_22};
	newmat->_33 = mat2_determinant(&temp);
	Mat3ransponse(newmat);
	mat3_mul_skalar(newmat , 1.f/mat3_determinant(m));
	return newmat;
}