const size_t mat4_size = sizeof(Mat4);

float 
mat4_determinant( const Mat4 *  _m){
	float determinant = 0.f;
	const Mat4 *  m = _m;
	Mat3 temp = { m->_22, m->_23, m->_24, 
					m->_32, m->_33, m->_34, 
					m->_42, m->_43, m->_44 };
	determinant += (m->_11 * mat3_determinant(&temp));
	temp = (Mat3) { m->_21, m->_23, m->_24, 
					  m->_31, m->_33, m->_34, 
					  m->_41, m->_43, m->_44 };
	//temp._11 = m->_21; 
	//temp._21 = m->_31; 
	//temp._31 = m->_41;
	determinant += (m->_12 * mat3_determinant(&temp));
	temp = (Mat3) { m->_21, m->_22, m->_24, 
					    m->_31, m->_32, m->_34, 
					    m->_41, m->_42, m->_44 };
	//temp._12 = m->_22; 
	//temp._22 = m->_32; 
	//temp._32 = m->_42;
	determinant += (m->_13 * mat3_determinant(&temp));
	temp = (Mat3) { m->_21, m->_22, m->_23, 
					  m->_31, m->_32, m->_33, 
					  m->_41, m->_42, m->_43 };
	//temp._13 = m->_23;
	//temp._23 = m->_33;
	//temp._33 = m->_43;
	determinant += (m->_14 * mat3_determinant(&temp));
	return determinant;
}

bool 
mat4_equals( const Mat4 *  m, const Mat4 *  m2){
	return (m == m2) || 
		   (m->_11 == m2->_11 &&
			m->_12 == m2->_12 &&
			m->_13 == m2->_13 &&
			m->_14 == m2->_14 &&
			m->_21 == m2->_21 &&
			m->_22 == m2->_22 &&
			m->_23 == m2->_23 &&
			m->_24 == m2->_24 &&
			m->_31 == m2->_31 &&
			m->_32 == m2->_32 &&
			m->_33 == m2->_33 &&
			m->_34 == m2->_34 &&
			m->_41 == m2->_41 &&
			m->_42 == m2->_42 &&
			m->_43 == m2->_43 &&
			m->_44 == m2->_44);
}

void 
Mat4ransponse( Mat4 *  m){
	float temp = m->_21;
	m->_21 = m->_12;
	m->_12 = temp;
	temp = m->_31;
	m->_31 = m->_13;
	m->_13 = temp;
	temp = m->_32;
	m->_32 = m->_23;
	m->_23 = temp;
	temp = m->_41;
	m->_41 = m->_14;
	m->_14 = temp;
	temp = m->_42;
	m->_42 = m->_24;
	m->_24 = temp;
	temp = m->_43;
	m->_43 = m->_34;
	m->_34 = temp;
}


Mat4 * 
Mat4ransponse_new(const Mat4 *  m){
	Mat4 *newmat = mat4_copy_new(m);
	Mat4ransponse(newmat);
	return newmat;
}

void
mat4_copy( Mat4 *  m, const Mat4 *  m2){
	m->_11 = m2->_11;
	m->_12 = m2->_12;
	m->_13 = m2->_13;
	m->_14 = m2->_14;
	m->_21 = m2->_21;
	m->_22 = m2->_22;
	m->_23 = m2->_23;
	m->_24 = m2->_24;
	m->_31 = m2->_31;
	m->_32 = m2->_32;
	m->_33 = m2->_33;
	m->_34 = m2->_34;
	m->_41 = m2->_41;
	m->_42 = m2->_42;
	m->_43 = m2->_43;
	m->_44 = m2->_44;
}

Mat4 * 
mat4_copy_new( const Mat4 *  m){
	Mat4 *newmat = malloc(mat4_size);
	mat4_copy(newmat, m);
	return newmat;
}

void
mat4_print( const Mat4 * m){
	#if 0
		//method cuts to stirng...must improve function for morze big numbers
	#endif
	printf("\n| %f %f %f %f |\n| %f %f %f %f |\n| %f %f %f %f |\n| %f %f %f %f |\n", m->_11, m->_12, m->_13, m->_14
																		, m->_21, m->_22, m->_23, m->_24
																		, m->_31, m->_32, m->_33, m->_34
																		, m->_41, m->_42, m->_43, m->_44);
}

void 
mat4_add( Mat4 *  m, const Mat4 *  m2){
	m->_11 += m2->_11;
	m->_12 += m2->_12;
	m->_13 += m2->_13;
	m->_14 += m2->_14;
	m->_21 += m2->_21;
	m->_22 += m2->_22;
	m->_23 += m2->_23;
	m->_24 += m2->_24;
	m->_31 += m2->_31;
	m->_32 += m2->_32;
	m->_33 += m2->_33;
	m->_34 += m2->_34;
	m->_41 += m2->_41;
	m->_42 += m2->_42;
	m->_43 += m2->_43;
	m->_44 += m2->_44;
}

Mat4 * 
mat4_add_new( const Mat4 *  m, const Mat4 *  m2){
	Mat4 *newmat = malloc(mat4_size);
	newmat->_11 = m->_11 + m2->_11;
	newmat->_12 = m->_12 + m2->_12;
	newmat->_13 = m->_13 + m2->_13;
	newmat->_14 = m->_14 + m2->_14;
	newmat->_21 = m->_21 + m2->_21;
	newmat->_22 = m->_22 + m2->_22;
	newmat->_23 = m->_23 + m2->_23;
	newmat->_24 = m->_24 + m2->_24;
	newmat->_31 = m->_31 + m2->_31;
	newmat->_32 = m->_32 + m2->_32;
	newmat->_33 = m->_33 + m2->_33;
	newmat->_34 = m->_34 + m2->_34;
	newmat->_41 = m->_41 + m2->_41;
	newmat->_42 = m->_42 + m2->_42;
	newmat->_43 = m->_43 + m2->_43;
	newmat->_44 = m->_44 + m2->_44;
	return newmat;
}

void 
mat4_sub( Mat4 *  m, const Mat4 *  m2){
	m->_11 -= m2->_11;
	m->_12 -= m2->_12;
	m->_13 -= m2->_13;
	m->_14 -= m2->_14;
	m->_21 -= m2->_21;
	m->_22 -= m2->_22;
	m->_23 -= m2->_23;
	m->_24 -= m2->_24;
	m->_31 -= m2->_31;
	m->_32 -= m2->_32;
	m->_33 -= m2->_33;
	m->_34 -= m2->_34;
	m->_41 -= m2->_41;
	m->_42 -= m2->_42;
	m->_43 -= m2->_43;
	m->_44 -= m2->_44;
}

Mat4 * 
mat4_sub_new( const Mat4 *  m, const Mat4 *  m2){
	Mat4 *newmat = malloc(mat4_size);
	newmat->_11 = m->_11 - m2->_11;
	newmat->_12 = m->_12 - m2->_12;
	newmat->_13 = m->_13 - m2->_13;
	newmat->_14 = m->_14 - m2->_14;
	newmat->_21 = m->_21 - m2->_21;
	newmat->_22 = m->_22 - m2->_22;
	newmat->_23 = m->_23 - m2->_23;
	newmat->_24 = m->_24 - m2->_24;
	newmat->_31 = m->_31 - m2->_31;
	newmat->_32 = m->_32 - m2->_32;
	newmat->_33 = m->_33 - m2->_33;
	newmat->_34 = m->_34 - m2->_34;
	newmat->_41 = m->_41 - m2->_41;
	newmat->_42 = m->_42 - m2->_42;
	newmat->_43 = m->_43 - m2->_43;
	newmat->_44 = m->_44 - m2->_44;
	return newmat;
}

void 
mat4_mul( Mat4 *  m, const Mat4 *  m2){
	Mat4 temp = {
		(m->_11 * m2->_11) + (m->_12 * m2->_21) + (m->_13 * m2->_31) + (m->_14 * m2->_41),
		(m->_11 * m2->_12) + (m->_12 * m2->_22) + (m->_13 * m2->_32) + (m->_14 * m2->_42),
		(m->_11 * m2->_13) + (m->_12 * m2->_23) + (m->_13 * m2->_33) + (m->_14 * m2->_43),
		(m->_11 * m2->_14) + (m->_12 * m2->_24) + (m->_13 * m2->_34) + (m->_14 * m2->_44),
		(m->_21 * m2->_11) + (m->_22 * m2->_21) + (m->_23 * m2->_31) + (m->_24 * m2->_41),
		(m->_21 * m2->_12) + (m->_22 * m2->_22) + (m->_23 * m2->_32) + (m->_24 * m2->_42),
		(m->_21 * m2->_13) + (m->_22 * m2->_23) + (m->_23 * m2->_33) + (m->_24 * m2->_43),
		(m->_21 * m2->_14) + (m->_22 * m2->_24) + (m->_23 * m2->_34) + (m->_24 * m2->_44),
		(m->_31 * m2->_11) + (m->_32 * m2->_21) + (m->_33 * m2->_31) + (m->_34 * m2->_41),
		(m->_31 * m2->_12) + (m->_32 * m2->_22) + (m->_33 * m2->_32) + (m->_34 * m2->_42),
		(m->_31 * m2->_13) + (m->_32 * m2->_23) + (m->_33 * m2->_33) + (m->_34 * m2->_43),
		(m->_31 * m2->_14) + (m->_32 * m2->_24) + (m->_33 * m2->_34) + (m->_34 * m2->_44),
		(m->_41 * m2->_11) + (m->_42 * m2->_21) + (m->_43 * m2->_31) + (m->_44 * m2->_41),
		(m->_41 * m2->_12) + (m->_42 * m2->_22) + (m->_43 * m2->_32) + (m->_44 * m2->_42),
		(m->_41 * m2->_13) + (m->_42 * m2->_23) + (m->_43 * m2->_33) + (m->_44 * m2->_43),
		(m->_41 * m2->_14) + (m->_42 * m2->_24) + (m->_43 * m2->_34) + (m->_44 * m2->_44)
	};
	mat4_copy(m, &temp);
}

void 
mat4_mul_dest( Mat4 * _dest, const Mat4 *   _m, const Mat4 * _m2){
	Mat4 * dest = _dest;
	const Mat4 *m = _m, *m2 = _m2;
	dest->_11 = (m->_11 * m2->_11) + (m->_12 * m2->_21) + (m->_13 * m2->_31) + (m->_14 * m2->_41);
	dest->_12 = (m->_11 * m2->_12) + (m->_12 * m2->_22) + (m->_13 * m2->_32) + (m->_14 * m2->_42);
	dest->_13 = (m->_11 * m2->_13) + (m->_12 * m2->_23) + (m->_13 * m2->_33) + (m->_14 * m2->_43);
	dest->_14 = (m->_11 * m2->_14) + (m->_12 * m2->_24) + (m->_13 * m2->_34) + (m->_14 * m2->_44);
	dest->_21 = (m->_21 * m2->_11) + (m->_22 * m2->_21) + (m->_23 * m2->_31) + (m->_24 * m2->_41);
	dest->_22 = (m->_21 * m2->_12) + (m->_22 * m2->_22) + (m->_23 * m2->_32) + (m->_24 * m2->_42);
	dest->_23 = (m->_21 * m2->_13) + (m->_22 * m2->_23) + (m->_23 * m2->_33) + (m->_24 * m2->_43);
	dest->_24 = (m->_21 * m2->_14) + (m->_22 * m2->_24) + (m->_23 * m2->_34) + (m->_24 * m2->_44);
	dest->_31 = (m->_31 * m2->_11) + (m->_32 * m2->_21) + (m->_33 * m2->_31) + (m->_34 * m2->_41);
	dest->_32 = (m->_31 * m2->_12) + (m->_32 * m2->_22) + (m->_33 * m2->_32) + (m->_34 * m2->_42);
	dest->_33 = (m->_31 * m2->_13) + (m->_32 * m2->_23) + (m->_33 * m2->_33) + (m->_34 * m2->_43);
	dest->_34 = (m->_31 * m2->_14) + (m->_32 * m2->_24) + (m->_33 * m2->_34) + (m->_34 * m2->_44);
	dest->_41 = (m->_41 * m2->_11) + (m->_42 * m2->_21) + (m->_43 * m2->_31) + (m->_44 * m2->_41);
	dest->_42 = (m->_41 * m2->_12) + (m->_42 * m2->_22) + (m->_43 * m2->_32) + (m->_44 * m2->_42);
	dest->_43 = (m->_41 * m2->_13) + (m->_42 * m2->_23) + (m->_43 * m2->_33) + (m->_44 * m2->_43);
	dest->_44 = (m->_41 * m2->_14) + (m->_42 * m2->_24) + (m->_43 * m2->_34) + (m->_44 * m2->_44);
}

Mat4 * 
mat4_mul_new( const Mat4 *   m, const Mat4 *   m2){
	Mat4 *newmat = malloc(mat4_size);
	newmat->_11 = (m->_11 * m2->_11) + (m->_12 * m2->_21) + (m->_13 * m2->_31) + (m->_14 * m2->_41);
	newmat->_12 = (m->_11 * m2->_12) + (m->_12 * m2->_22) + (m->_13 * m2->_32) + (m->_14 * m2->_42);
	newmat->_13 = (m->_11 * m2->_13) + (m->_12 * m2->_23) + (m->_13 * m2->_33) + (m->_14 * m2->_43);
	newmat->_14 = (m->_11 * m2->_14) + (m->_12 * m2->_24) + (m->_13 * m2->_34) + (m->_14 * m2->_44);
	newmat->_21 = (m->_21 * m2->_11) + (m->_22 * m2->_21) + (m->_23 * m2->_31) + (m->_24 * m2->_41);
	newmat->_22 = (m->_21 * m2->_12) + (m->_22 * m2->_22) + (m->_23 * m2->_32) + (m->_24 * m2->_42);
	newmat->_23 = (m->_21 * m2->_13) + (m->_22 * m2->_23) + (m->_23 * m2->_33) + (m->_24 * m2->_43);
	newmat->_24 = (m->_21 * m2->_14) + (m->_22 * m2->_24) + (m->_23 * m2->_34) + (m->_24 * m2->_44);
	newmat->_31 = (m->_31 * m2->_11) + (m->_32 * m2->_21) + (m->_33 * m2->_31) + (m->_34 * m2->_41);
	newmat->_32 = (m->_31 * m2->_12) + (m->_32 * m2->_22) + (m->_33 * m2->_32) + (m->_34 * m2->_42);
	newmat->_33 = (m->_31 * m2->_13) + (m->_32 * m2->_23) + (m->_33 * m2->_33) + (m->_34 * m2->_43);
	newmat->_34 = (m->_31 * m2->_14) + (m->_32 * m2->_24) + (m->_33 * m2->_34) + (m->_34 * m2->_44);
	newmat->_41 = (m->_41 * m2->_11) + (m->_42 * m2->_21) + (m->_43 * m2->_31) + (m->_44 * m2->_41);
	newmat->_42 = (m->_41 * m2->_12) + (m->_42 * m2->_22) + (m->_43 * m2->_32) + (m->_44 * m2->_42);
	newmat->_43 = (m->_41 * m2->_13) + (m->_42 * m2->_23) + (m->_43 * m2->_33) + (m->_44 * m2->_43);
	newmat->_44 = (m->_41 * m2->_14) + (m->_42 * m2->_24) + (m->_43 * m2->_34) + (m->_44 * m2->_44);
	return newmat;
}

void 
mat4_mul_skalar( Mat4 *   m, const float skalar){
	m->_11 *= skalar;
	m->_12 *= skalar;
	m->_13 *= skalar;
	m->_14 *= skalar;
	m->_21 *= skalar;
	m->_22 *= skalar;
	m->_23 *= skalar;
	m->_24 *= skalar;
	m->_31 *= skalar;
	m->_32 *= skalar;
	m->_33 *= skalar;
	m->_34 *= skalar;
	m->_41 *= skalar;
	m->_42 *= skalar;
	m->_43 *= skalar;
	m->_44 *= skalar;
}

Mat4 * 
mat4_mul_skalar_new( const Mat4 *   m, const float skalar) {
	Mat4 *newmat = malloc(mat4_size);
	mat4_copy(newmat, m);
	mat4_mul_skalar(newmat, skalar);
	return newmat;
}

void 
mat4_inverse( Mat4 *   m){
	Mat3 temp = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	Mat4 * cof_mat4 = malloc(mat4_size);
	temp = (Mat3) { m->_22, m->_23, m->_24, m->_32, m->_33, m->_34, m->_42, m->_43, m->_44};
	cof_mat4->_11 = mat3_determinant(&temp);
	temp = (Mat3) { m->_21, m->_23, m->_24, m->_31, m->_33, m->_34, m->_41, m->_43, m->_44};
	cof_mat4->_12 = -mat3_determinant(&temp);
	temp = (Mat3) { m->_21, m->_22, m->_24, m->_31, m->_32, m->_34, m->_41, m->_42, m->_44};
	cof_mat4->_13 = mat3_determinant(&temp);
	temp = (Mat3) { m->_21, m->_22, m->_23, m->_31, m->_32, m->_33, m->_41, m->_42, m->_43};
	cof_mat4->_14 = -mat3_determinant(&temp);
	
	temp = (Mat3) { m->_12, m->_13, m->_14, m->_32, m->_33, m->_34, m->_42, m->_43, m->_44};
	cof_mat4->_21 = -mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_13, m->_14, m->_31, m->_33, m->_34, m->_41, m->_43, m->_44};
	cof_mat4->_22 = mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_12, m->_14, m->_31, m->_32, m->_34, m->_41, m->_42, m->_44};
	cof_mat4->_23 = -mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_12, m->_13, m->_31, m->_32, m->_33, m->_41, m->_42, m->_43};
	cof_mat4->_24 = mat3_determinant(&temp);
	
	temp = (Mat3) { m->_12, m->_13, m->_14, m->_22, m->_23, m->_24, m->_42, m->_43, m->_44};
	cof_mat4->_31 = mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_13, m->_14, m->_21, m->_23, m->_24, m->_41, m->_43, m->_44};
	cof_mat4->_32 = -mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_12, m->_14, m->_21, m->_22, m->_24, m->_41, m->_42, m->_44};
	cof_mat4->_33 = mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_12, m->_13, m->_21, m->_22, m->_23, m->_41, m->_42, m->_43};
	cof_mat4->_34 = -mat3_determinant(&temp);
	
	temp = (Mat3) { m->_12, m->_13, m->_14, m->_22, m->_23, m->_24, m->_32, m->_33, m->_34};
	cof_mat4->_41 = -mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_13, m->_14, m->_21, m->_23, m->_24, m->_31, m->_33, m->_34};
	cof_mat4->_42 = mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_12, m->_14, m->_21, m->_22, m->_24, m->_31, m->_32, m->_34};
	cof_mat4->_43 = -mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_12, m->_13, m->_21, m->_22, m->_23, m->_31, m->_32, m->_33};
	cof_mat4->_44 = mat3_determinant(&temp);
	
	Mat4ransponse(cof_mat4);
	mat4_mul_skalar(cof_mat4 , 1.f/mat4_determinant(m));
	mat4_copy(m, cof_mat4);
	free(cof_mat4);
}

void mat4_inverse_dest(Mat4 * _dest, const Mat4 * _m)
{
	const Mat4 * m = _m;
	Mat4 * dest = _dest;
	Mat3 temp = { m->_22, m->_23, m->_24, 
				    m->_32, m->_33, m->_34, 
				    m->_42, m->_43, m->_44};
	//temp._11 = m->_12; temp._12 = m->_23; temp._13 = m->_24; 
	//temp._21 = m->_32; temp._22 = m->_33; temp._23 = m->_34; 
	//temp._31 = m->_42; temp._32 = m->_43; temp._33 = m->_44;
	dest->_11 = ((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	//temp = (Mat3) { m->_21, m->_23, m->_24, 
	//					m->_31, m->_33, m->_34, 
	//					m->_41, m->_43, m->_44};
	temp._11 = m->_21; temp._21 = m->_31; temp._31 = m->_41;
	dest->_12 = -((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	//temp = (Mat3) { m->_21, m->_22, m->_24, 
	//				    m->_31, m->_32, m->_34, 
	//				    m->_41, m->_42, m->_44};
	temp._12 = m->_22; temp._22 = m->_32; temp._32 = m->_42;
	dest->_13 = ((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	temp = (Mat3) { m->_21, m->_22, m->_23, 
					    m->_31, m->_32, m->_33, 
					    m->_41, m->_42, m->_43};
	//temp._13 = m->_23; temp._23 = m->_33; temp._33 = m->_43;
	dest->_14 = -((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	//temp = (Mat3) { m->_12, m->_13, m->_14, 
	//				    m->_32, m->_33, m->_34, 
	//				    m->_42, m->_43, m->_44};
	temp._11 = m->_12; temp._12 = m->_13; temp._13 = m->_14; 
	temp._21 = m->_32; temp._22 = m->_33; temp._23 = m->_34; 
	temp._31 = m->_42; temp._32 = m->_43; temp._33 = m->_44;
	dest->_21 = -((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	//temp = (Mat3) { m->_11, m->_13, m->_14, 
	//				    m->_31, m->_33, m->_34, 
	//				    m->_41, m->_43, m->_44};
	temp._11 = m->_11; temp._21 = m->_31; temp._31 = m->_41;
	dest->_22 = ((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	//temp = (Mat3) { m->_11, m->_12, m->_14, 
	//				    m->_31, m->_32, m->_34, 
	//				    m->_41, m->_42, m->_44};
	temp._12 = m->_12; temp._22 = m->_32; temp._32 = m->_42;
	dest->_23 = -((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	//temp = (Mat3) { m->_11, m->_12, m->_13, 
	//				    m->_31, m->_32, m->_33, 
	//				    m->_41, m->_42, m->_43};
	temp._13 = m->_13; temp._23 = m->_33; temp._33 = m->_43;
	dest->_24 = ((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	
	//temp = (Mat3) { m->_12, m->_13, m->_14, 
	//				    m->_22, m->_23, m->_24, 
	//				    m->_42, m->_43, m->_44};
	temp._11 = m->_12; temp._12 = m->_13; temp._13 = m->_14; 
	temp._21 = m->_22; temp._22 = m->_23; temp._23 = m->_24; 
	temp._31 = m->_42; temp._32 = m->_43; temp._33 = m->_44;
	dest->_31 = ((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	//temp = (Mat3) { m->_11, m->_13, m->_14, 
	//				    m->_21, m->_23, m->_24, 
	//				    m->_41, m->_43, m->_44};
	temp._11 = m->_11; temp._21 = m->_21; temp._31 = m->_41;
	dest->_32 = -((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	//temp = (Mat3) { m->_11, m->_12, m->_14, 
	//				    m->_21, m->_22, m->_24, 
	//				    m->_41, m->_42, m->_44};
	temp._12 = m->_12; temp._22 = m->_22; temp._32 = m->_42;
	dest->_33 = ((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	//temp = (Mat3) { m->_11, m->_12, m->_13, 
	//                  m->_21, m->_22, m->_23, 
	//				    m->_41, m->_42, m->_43};
	temp._13 = m->_13; temp._23 = m->_23; temp._33 = m->_43;
	dest->_34 = -((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	
	//temp = (Mat3) { m->_12, m->_13, m->_14, 
	//			        m->_22, m->_23, m->_24, 
	//				    m->_32, m->_33, m->_34};
	temp._11 = m->_12; temp._12 = m->_13; temp._13 = m->_14; 
	temp._21 = m->_22; temp._22 = m->_23; temp._23 = m->_24; 
	temp._31 = m->_32; temp._32 = m->_33; temp._33 = m->_34;
	dest->_41 = -((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	//temp = (Mat3) { m->_11, m->_13, m->_14, 
	//				    m->_21, m->_23, m->_24, 
	//				    m->_31, m->_33, m->_34};
	temp._11 = m->_11; temp._21 = m->_21; temp._31 = m->_31;
	dest->_42 = ((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	//temp = (Mat3) { m->_11, m->_12, m->_14, 
	//				    m->_21, m->_22, m->_24, 
	//				    m->_31, m->_32, m->_34};
	temp._12 = m->_12; temp._22 = m->_22; temp._32 = m->_32;
	dest->_43 = -((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	//temp = (Mat3) { m->_11, m->_12, m->_13, 
	//				    m->_21, m->_22, m->_23, 
	//				    m->_31, m->_32, m->_33};
	temp._13 = m->_13; temp._23 = m->_23; temp._33 = m->_33;
	dest->_44 = ((temp._11*temp._22*temp._33) +
				(temp._12*temp._23*temp._31) + 
				(temp._13*temp._21*temp._32) -
				(temp._13*temp._22*temp._31) -
				(temp._12*temp._21*temp._33) -
				(temp._11*temp._23*temp._32));//mat3_determinant(&temp);
	
	Mat4ransponse(dest);
	mat4_mul_skalar(dest , 1.f/mat4_determinant(m));
}

Mat4 * 
mat4_inverse_new( const Mat4 *  m){
	Mat3 temp = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	Mat4 * newmat = malloc(mat4_size);
	temp = (Mat3) { m->_22, m->_23, m->_24, m->_32, m->_33, m->_34, m->_42, m->_43, m->_44};
	newmat->_11 = mat3_determinant(&temp);
	temp = (Mat3) { m->_21, m->_23, m->_24, m->_31, m->_33, m->_34, m->_41, m->_43, m->_44};
	newmat->_12 = -mat3_determinant(&temp);
	temp = (Mat3) { m->_21, m->_22, m->_24, m->_31, m->_32, m->_34, m->_41, m->_42, m->_44};
	newmat->_13 = mat3_determinant(&temp);
	temp = (Mat3) { m->_21, m->_22, m->_23, m->_31, m->_32, m->_33, m->_41, m->_42, m->_43};
	newmat->_14 = -mat3_determinant(&temp);
	
	temp = (Mat3) { m->_12, m->_13, m->_14, m->_32, m->_33, m->_34, m->_42, m->_43, m->_44};
	newmat->_21 = -mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_13, m->_14, m->_31, m->_33, m->_34, m->_41, m->_43, m->_44};
	newmat->_22 = mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_12, m->_14, m->_31, m->_32, m->_34, m->_41, m->_42, m->_44};
	newmat->_23 = -mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_12, m->_13, m->_31, m->_32, m->_33, m->_41, m->_42, m->_43};
	newmat->_24 = mat3_determinant(&temp);
	
	temp = (Mat3) { m->_12, m->_13, m->_14, m->_22, m->_23, m->_24, m->_42, m->_43, m->_44};
	newmat->_31 = mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_13, m->_14, m->_21, m->_23, m->_24, m->_41, m->_43, m->_44};
	newmat->_32 = -mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_12, m->_14, m->_21, m->_22, m->_24, m->_41, m->_42, m->_44};
	newmat->_33 = mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_12, m->_13, m->_21, m->_22, m->_23, m->_41, m->_42, m->_43};
	newmat->_34 = -mat3_determinant(&temp);
	
	temp = (Mat3) { m->_12, m->_13, m->_14, m->_22, m->_23, m->_24, m->_32, m->_33, m->_34};
	newmat->_41 = -mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_13, m->_14, m->_21, m->_23, m->_24, m->_31, m->_33, m->_34};
	newmat->_42 = mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_12, m->_14, m->_21, m->_22, m->_24, m->_31, m->_32, m->_34};
	newmat->_43 = -mat3_determinant(&temp);
	temp = (Mat3) { m->_11, m->_12, m->_13, m->_21, m->_22, m->_23, m->_31, m->_32, m->_33};
	newmat->_44 = mat3_determinant(&temp);
	
	Mat4ransponse(newmat);
	mat4_mul_skalar(newmat , 1.f/mat4_determinant(m));
	
	return newmat;
}
