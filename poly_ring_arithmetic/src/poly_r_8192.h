/*
 * poly_r_8096.c
 *
 *  Created on: Apr 14, 2020
 *      Author: yoda
 */

#ifndef POLY_R_8096_C_
#define POLY_R_8096_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "gf_mul.h"
typedef uint64_t element_p;

/*
 * Elements of R.<x> = GF(2)[X]/(X^n + 1). Represents polynomial
 * (coeffs[0] & 0x1) + X*( coeffs[0] << 0x2) + ...+ X^63*(coeffs[0] & 0x8000000000000000 ) + ... +
 * X^{8096}*(coeffs[])
 */
typedef struct{
  element_p coeffs[128];
} poly;



extern poly * create_polynomial();

extern void set_pos(int pos, poly *polynomial);

extern void print_polynomial(poly *polynomial);

extern void flip_pos(int pos, poly *polynomial);

extern void add_poly(poly *result, const poly *p1, const poly *p2);

extern void mul_poly(poly *result, const poly *p1, const poly *p2);

extern void div_poly(poly *result, const poly p1, const poly *p2);

extern unsigned long get_deg(const poly *p);

extern unsigned long long  pop_count(const poly *p2);



#endif /* POLY_R_8096_C_ */
