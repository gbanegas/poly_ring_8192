/*
 * poly_r_8096.c
 *
 *  Created on: Apr 14, 2020
 *      Author: yoda
 */

#include "poly_r_8096.h"

poly* create_polynomial() {
	poly *polynomial = (poly*) calloc(1, sizeof(poly));
	return polynomial;
}

void set_pos(int pos, poly *polynomial) {
	unsigned long long one = 1;
	int idx_block = pos / 64;
	int idx_pos = 64 - ((idx_block * 64) - pos);
	polynomial->coeffs[idx_block] = polynomial->coeffs[idx_block]
			| (one << idx_pos);

}

void flip_pos(int pos, poly *polynomial) {
	unsigned long long one = 1;
	int idx_block = pos / 64;
	int idx_pos = 64 - ((idx_block * 64) - pos);

	polynomial->coeffs[idx_block] = (polynomial->coeffs[idx_block]	^ (one << idx_pos));

}

void print_polynomia(poly *polynomial) {

	int idx = 0;
	unsigned long long one = 1;
	for (int i = 0; i < 127; i++) {
		for (unsigned long long j = 0; j < 64; j++) {
			unsigned long long result = (one << j);
			if (polynomial->coeffs[i] & result) {
				if (idx != 0)
					printf("x^%d +", idx);
				else
					printf("1 +");
			}
			idx++;
		}
	}
	printf("\n");

}
