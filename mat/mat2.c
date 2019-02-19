const size_t mat2_size = sizeof(mat2_t);

float 
mat2_determinant( const mat2_t *  m){
	return (m->_11*m->_22)-(m->_12*m->_21);
}

bool 
mat2_equals( const mat2_t *  m, const mat2_t *  m2){
	return (m == m2) || 
		   (m->_11 == m2->_11 &&
			m->_12 == m2->_12 &&
			m->_21 == m2->_21 &&
			m->_22 == m2->_22);
}

void 
mat2_transponse( mat2_t *  m){
	float temp = m->_21;
	m->_21 = m->_12;
	m->_12 = temp;
}


mat2_t * 
mat2_transponse_new(const mat2_t *  m){
	mat2_t *newmat = mat2_copy_new(m);
	mat2_transponse(newmat);
	return newmat;
}

void
mat2_copy( mat2_t *  m, const mat2_t *  m2){
	m->_11 = m2->_11;
	m->_12 = m2->_12;
	m->_21 = m2->_21;
	m->_22 = m2->_22;
}

mat2_t * 
mat2_copy_new( const mat2_t *  m){
	mat2_t *newmat = malloc(mat2_size);
	mat2_copy(newmat, m);
	return newmat;
}

void
mat2_print( const mat2_t *   m){
	printf("\n| %f %f |\n| %f %f |\n", m->_11, m->_12, m->_21, m->_22);
}

void 
mat2_add( mat2_t *   m, const mat2_t *   m2){
	m->_11 += m2->_11;
	m->_12 += m2->_12;
	m->_21 += m2->_21;
	m->_22 += m2->_22;
}

mat2_t * 
mat2_add_new( const mat2_t *   m, const mat2_t *   m2){
	mat2_t *newmat = malloc(mat2_size);
	newmat->_11 = m->_11 + m2->_11;
	newmat->_12 = m->_12 + m2->_12;
	newmat->_21 = m->_21 + m2->_21;
	newmat->_22 = m->_22 + m2->_22;
	return newmat;
}

void 
mat2_sub( mat2_t *   m, const mat2_t *   m2){
	m->_11 -= m2->_11;
	m->_12 -= m2->_12;
	m->_21 -= m2->_21;
	m->_22 -= m2->_22;
}

mat2_t * 
mat2_sub_new( const mat2_t *   m, const mat2_t *   m2){
	mat2_t *newmat = malloc(mat2_size);
	newmat->_11 = m->_11 - m2->_11;
	newmat->_12 = m->_12 - m2->_12;
	newmat->_21 = m->_21 - m2->_21;
	newmat->_22 = m->_22 - m2->_22;
	return newmat;
}

void 
mat2_mul( mat2_t *   m, const mat2_t *   m2){
	mat2_t temp = {
		(m->_11 * m2->_11) + (m->_12 * m2->_21),
		(m->_11 * m2->_12) + (m->_12 * m2->_22),
		(m->_21 * m2->_11) + (m->_22 * m2->_21),
		(m->_21 * m2->_12) + (m->_22 * m2->_22)
	};
	mat2_copy(m, &temp);
}

mat2_t * 
mat2_mul_new( const mat2_t *   m, const mat2_t *   m2){
	mat2_t * newmat = malloc(mat2_size);
	newmat->_11 = (m->_11 * m2->_11) + (m->_12 * m2->_21);
	newmat->_12 = (m->_11 * m2->_12) + (m->_12 * m2->_22);
	newmat->_21 = (m->_21 * m2->_11) + (m->_22 * m2->_21);
	newmat->_22 = (m->_21 * m2->_12) + (m->_22 * m2->_22);
	return newmat;
}

void 
mat2_mul_skalar( mat2_t *   m, const float skalar){
	m->_11 *= skalar;
	m->_12 *= skalar;
	m->_21 *= skalar;
	m->_22 *= skalar;
}

mat2_t * 
mat2_mul_skalar_new(const mat2_t *   m, const float skalar) {
	mat2_t *newmat = malloc(mat2_size);
	mat2_copy(newmat, m);
	mat2_mul_skalar(newmat, skalar);
	return newmat;
}

void 
mat2_inverse( mat2_t *   m){
	mat2_t cof_mat2 = (mat2_t) { m->_22, -m->_21, -m->_12, m->_11 };
	mat2_transponse(&cof_mat2);
	mat2_mul_skalar(&cof_mat2 , 1.f/mat2_determinant(m));
	mat2_copy(m, &cof_mat2);
}

void mat2_inverse_dest( mat2_t *   dest, const mat2_t *   m) {
	dest->_11 = m->_22;
	dest->_12 = -m->_21;
	dest->_21 = -m->_12;
	dest->_22 = m->_11;
	mat2_transponse(dest);
	mat2_mul_skalar(dest , 1.f/mat2_determinant(m));
}

mat2_t * 
mat2_inverse_new(const mat2_t *   m){
	mat2_t *newmat = malloc(mat2_size);
	mat2_t cof_mat2 = (mat2_t) { m->_22, -m->_21, -m->_12, m->_11 };
	mat2_copy(newmat, &cof_mat2);
	mat2_transponse(newmat);
	mat2_mul_skalar(newmat , 1.f/mat2_determinant(m));
	return newmat;
}