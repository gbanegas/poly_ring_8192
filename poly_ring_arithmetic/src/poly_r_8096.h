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

/*
 * Elements of R.<x> = GF(2)[X]/(X^n + 1). Represents polynomial
 * (coeffs[0] & 0x1) + X*( coeffs[0] << 0x2) + ...+ X^63*(coeffs[0] & 0x8000000000000000 ) + ... +
 * X^{8096}*(coeffs[])
 */
typedef struct{
  unsigned long long coeffs[127];
} poly;



extern poly * create_polynomial();

extern void set_pos(int pos, poly *polynomial);

extern void print_polynomia(poly *polynomial);

extern void flip_pos(int pos, poly *polynomial);

#endif /* POLY_R_8096_C_ */
