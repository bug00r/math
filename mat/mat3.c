const size_t mat3_size = sizeof(mat3_t);

float 
mat3_determinant(const mat3_t *  m){
	return (m->_11*m->_22*m->_33) +
		   (m->_12*m->_23*m->_31) + 
		   (m->_13*m->_21*m->_32) -
		   (m->_13*m->_22*m->_31) -
		   (m->_12*m->_21*m->_33) -
		   (m->_11*m->_23*m->_32);
}

bool 
mat3_equals( const mat3_t *  m, const mat3_t *  m2){
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
mat3_transponse( mat3_t *  m){
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


mat3_t * 
mat3_transponse_new( const mat3_t * m){
	mat3_t *newmat = mat3_copy_new(m);
	mat3_transponse(newmat);
	return newmat;
}

void
mat3_copy( mat3_t *  m, const mat3_t *  m2){
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

mat3_t * 
mat3_copy_new( const mat3_t *  m){
	mat3_t *newmat = malloc(mat3_size);
	mat3_copy(newmat, m);
	return newmat;
}

void
mat3_print( const mat3_t *   m){
	#if 0
		//method cuts to stirng...must improve function for morze big numbers
	#endif
	printf("\n| %f %f %f |\n| %f %f %f |\n| %f %f %f |\n", m->_11, m->_12, m->_13, 
															m->_21, m->_22, m->_23, 
															m->_31, m->_32, m->_33);
}

void 
mat3_add( mat3_t *   m, const mat3_t *   m2){
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

mat3_t * 
mat3_add_new( const mat3_t *   m, const mat3_t *   m2){
	mat3_t *newmat = malloc(mat3_size);
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
mat3_sub( mat3_t *   m, const mat3_t *   m2){
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

mat3_t * 
mat3_sub_new( const mat3_t *   m, const mat3_t *   m2){
	mat3_t *newmat = malloc(mat3_size);
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
mat3_mul( mat3_t *   m, const mat3_t *   m2){
	mat3_t temp = {
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

mat3_t * 
mat3_mul_new( const mat3_t *   m, const mat3_t *   m2){
	mat3_t *newmat = malloc(mat3_size);
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

mat3_t * 
mat3_mul_dest(mat3_t * dest, const mat3_t *   m, const mat3_t *   m2){
	mat3_t *newmat = dest;
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
mat3_mul_skalar( mat3_t *   m, const float skalar){
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

mat3_t * 
mat3_mul_skalar_new( const mat3_t *   m, const float skalar) {
	mat3_t *newmat = malloc(mat3_size);
	mat3_copy(newmat, m);
	mat3_mul_skalar(newmat, skalar);
	return newmat;
}

void 
mat3_inverse( mat3_t *  m){
	mat2_t temp = {0.f, 0.f, 0.f, 0.f};
	mat3_t * cof_mat3 = malloc(mat3_size);
	temp = (mat2_t) { m->_22, m->_23, m->_32, m->_33};
	cof_mat3->_11 = mat2_determinant(&temp);
	temp = (mat2_t) { m->_21, m->_23, m->_31, m->_33};
	cof_mat3->_12 = -mat2_determinant(&temp);
	temp = (mat2_t) { m->_21, m->_22, m->_31, m->_32};
	cof_mat3->_13 = mat2_determinant(&temp);
	
	temp = (mat2_t) { m->_12, m->_13, m->_32, m->_33};
	cof_mat3->_21 = -mat2_determinant(&temp);
	temp = (mat2_t) { m->_11, m->_13, m->_31, m->_33};
	cof_mat3->_22 = mat2_determinant(&temp);
	temp = (mat2_t) { m->_11, m->_12, m->_31, m->_32};
	cof_mat3->_23 = -mat2_determinant(&temp);
	
	temp = (mat2_t) { m->_12, m->_13, m->_22, m->_23};
	cof_mat3->_31 = mat2_determinant(&temp);
	temp = (mat2_t) { m->_11, m->_13, m->_21, m->_23};
	cof_mat3->_32 = -mat2_determinant(&temp);
	temp = (mat2_t) { m->_11, m->_12, m->_21, m->_22};
	cof_mat3->_33 = mat2_determinant(&temp);
	
	mat3_transponse(cof_mat3);
	mat3_mul_skalar(cof_mat3 , 1.f/mat3_determinant(m));
	mat3_copy(m, cof_mat3);
	free(cof_mat3);
}

void mat3_inverse_dest( mat3_t *   dest, const mat3_t *   m) {
	mat2_t temp = {0.f, 0.f, 0.f, 0.f};
	temp = (mat2_t) { m->_22, m->_23, m->_32, m->_33};
	dest->_11 = mat2_determinant(&temp);
	temp = (mat2_t) { m->_21, m->_23, m->_31, m->_33};
	dest->_12 = -mat2_determinant(&temp);
	temp = (mat2_t) { m->_21, m->_22, m->_31, m->_32};
	dest->_13 = mat2_determinant(&temp);
	
	temp = (mat2_t) { m->_12, m->_13, m->_32, m->_33};
	dest->_21 = -mat2_determinant(&temp);
	temp = (mat2_t) { m->_11, m->_13, m->_31, m->_33};
	dest->_22 = mat2_determinant(&temp);
	temp = (mat2_t) { m->_11, m->_12, m->_31, m->_32};
	dest->_23 = -mat2_determinant(&temp);
	
	temp = (mat2_t) { m->_12, m->_13, m->_22, m->_23};
	dest->_31 = mat2_determinant(&temp);
	temp = (mat2_t) { m->_11, m->_13, m->_21, m->_23};
	dest->_32 = -mat2_determinant(&temp);
	temp = (mat2_t) { m->_11, m->_12, m->_21, m->_22};
	dest->_33 = mat2_determinant(&temp);
	mat3_transponse(dest);
	mat3_mul_skalar(dest , 1.f/mat3_determinant(m));
}

mat3_t * 
mat3_inverse_new( const mat3_t *   m){
	mat2_t temp = {0.f, 0.f, 0.f, 0.f};
	mat3_t * newmat = malloc(mat3_size);
	temp = (mat2_t) { m->_22, m->_23, m->_32, m->_33};
	newmat->_11 = mat2_determinant(&temp);
	temp = (mat2_t) { m->_21, m->_23, m->_31, m->_33};
	newmat->_12 = -mat2_determinant(&temp);
	temp = (mat2_t) { m->_21, m->_22, m->_31, m->_32};
	newmat->_13 = mat2_determinant(&temp);
	
	temp = (mat2_t) { m->_12, m->_13, m->_32, m->_33};
	newmat->_21 = -mat2_determinant(&temp);
	temp = (mat2_t) { m->_11, m->_13, m->_31, m->_33};
	newmat->_22 = mat2_determinant(&temp);
	temp = (mat2_t) { m->_11, m->_12, m->_31, m->_32};
	newmat->_23 = -mat2_determinant(&temp);
	
	temp = (mat2_t) { m->_12, m->_13, m->_22, m->_23};
	newmat->_31 = mat2_determinant(&temp);
	temp = (mat2_t) { m->_11, m->_13, m->_21, m->_23};
	newmat->_32 = -mat2_determinant(&temp);
	temp = (mat2_t) { m->_11, m->_12, m->_21, m->_22};
	newmat->_33 = mat2_determinant(&temp);
	mat3_transponse(newmat);
	mat3_mul_skalar(newmat , 1.f/mat3_determinant(m));
	return newmat;
}