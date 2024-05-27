const size_t mat2_size = sizeof(Mat2);

float 
mat2_determinant( const Mat2 *  m){
	return (m->_11*m->_22)-(m->_12*m->_21);
}

bool 
mat2_equals( const Mat2 *  m, const Mat2 *  m2){
	return (m == m2) || 
		   (m->_11 == m2->_11 &&
			m->_12 == m2->_12 &&
			m->_21 == m2->_21 &&
			m->_22 == m2->_22);
}

void 
Mat2ransponse( Mat2 *  m){
	float temp = m->_21;
	m->_21 = m->_12;
	m->_12 = temp;
}


Mat2 * 
Mat2ransponse_new(const Mat2 *  m){
	Mat2 *newmat = mat2_copy_new(m);
	Mat2ransponse(newmat);
	return newmat;
}

void
mat2_copy( Mat2 *  m, const Mat2 *  m2){
	m->_11 = m2->_11;
	m->_12 = m2->_12;
	m->_21 = m2->_21;
	m->_22 = m2->_22;
}

Mat2 * 
mat2_copy_new( const Mat2 *  m){
	Mat2 *newmat = malloc(mat2_size);
	mat2_copy(newmat, m);
	return newmat;
}

void
mat2_print( const Mat2 *   m){
	printf("\n| %f %f |\n| %f %f |\n", m->_11, m->_12, m->_21, m->_22);
}

void 
mat2_add( Mat2 *   m, const Mat2 *   m2){
	m->_11 += m2->_11;
	m->_12 += m2->_12;
	m->_21 += m2->_21;
	m->_22 += m2->_22;
}

Mat2 * 
mat2_add_new( const Mat2 *   m, const Mat2 *   m2){
	Mat2 *newmat = malloc(mat2_size);
	newmat->_11 = m->_11 + m2->_11;
	newmat->_12 = m->_12 + m2->_12;
	newmat->_21 = m->_21 + m2->_21;
	newmat->_22 = m->_22 + m2->_22;
	return newmat;
}

void 
mat2_sub( Mat2 *   m, const Mat2 *   m2){
	m->_11 -= m2->_11;
	m->_12 -= m2->_12;
	m->_21 -= m2->_21;
	m->_22 -= m2->_22;
}

Mat2 * 
mat2_sub_new( const Mat2 *   m, const Mat2 *   m2){
	Mat2 *newmat = malloc(mat2_size);
	newmat->_11 = m->_11 - m2->_11;
	newmat->_12 = m->_12 - m2->_12;
	newmat->_21 = m->_21 - m2->_21;
	newmat->_22 = m->_22 - m2->_22;
	return newmat;
}

void 
mat2_mul( Mat2 *   m, const Mat2 *   m2){
	Mat2 temp = {
		(m->_11 * m2->_11) + (m->_12 * m2->_21),
		(m->_11 * m2->_12) + (m->_12 * m2->_22),
		(m->_21 * m2->_11) + (m->_22 * m2->_21),
		(m->_21 * m2->_12) + (m->_22 * m2->_22)
	};
	mat2_copy(m, &temp);
}

Mat2 * 
mat2_mul_new( const Mat2 *   m, const Mat2 *   m2){
	Mat2 * newmat = malloc(mat2_size);
	newmat->_11 = (m->_11 * m2->_11) + (m->_12 * m2->_21);
	newmat->_12 = (m->_11 * m2->_12) + (m->_12 * m2->_22);
	newmat->_21 = (m->_21 * m2->_11) + (m->_22 * m2->_21);
	newmat->_22 = (m->_21 * m2->_12) + (m->_22 * m2->_22);
	return newmat;
}

void 
mat2_mul_skalar( Mat2 *   m, const float skalar){
	m->_11 *= skalar;
	m->_12 *= skalar;
	m->_21 *= skalar;
	m->_22 *= skalar;
}

Mat2 * 
mat2_mul_skalar_new(const Mat2 *   m, const float skalar) {
	Mat2 *newmat = malloc(mat2_size);
	mat2_copy(newmat, m);
	mat2_mul_skalar(newmat, skalar);
	return newmat;
}

void 
mat2_inverse( Mat2 *   m){
	Mat2 cof_mat2 = (Mat2) { m->_22, -m->_21, -m->_12, m->_11 };
	Mat2ransponse(&cof_mat2);
	mat2_mul_skalar(&cof_mat2 , 1.f/mat2_determinant(m));
	mat2_copy(m, &cof_mat2);
}

void mat2_inverse_dest( Mat2 *   dest, const Mat2 *   m) {
	dest->_11 = m->_22;
	dest->_12 = -m->_21;
	dest->_21 = -m->_12;
	dest->_22 = m->_11;
	Mat2ransponse(dest);
	mat2_mul_skalar(dest , 1.f/mat2_determinant(m));
}

Mat2 * 
mat2_inverse_new(const Mat2 *   m){
	Mat2 *newmat = malloc(mat2_size);
	Mat2 cof_mat2 = (Mat2) { m->_22, -m->_21, -m->_12, m->_11 };
	mat2_copy(newmat, &cof_mat2);
	Mat2ransponse(newmat);
	mat2_mul_skalar(newmat , 1.f/mat2_determinant(m));
	return newmat;
}