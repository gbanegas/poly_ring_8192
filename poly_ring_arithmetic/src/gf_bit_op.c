/*
 * gf_bit_op.c
 *
 *  Created on: Apr 15, 2020
 *      Author: yoda
 */

#include "gf_bit_op.h"

/*----------------------------------------------------------------------------*/

void right_bit_shift(const int length, element_p in[]) {
	int j;
	__m256i a, b;
	for (j = length - 1; j > 4; j = j - 4) {

		a = _mm256_lddqu_si256((__m256i*) &in[j - 3]); //load from in[j-3] to in[j]
		b = _mm256_lddqu_si256((__m256i*) &in[j - 4]); //load from in[j-4] to in[j-1]

		a = _mm256_slli_epi64(a, 1);
		b = _mm256_srli_epi64(b, (64 - 1));

		_mm256_storeu_si256(((__m256i*) &in[j - 3]), _mm256_or_si256(a, b));

	}
	for (; j > 0; j--) {
		in[j] <<= 1;
		in[j] |= (in[j - 1] & (element_p) 0x01) << (64 - 1);
	}
	in[j] <<= 1;

} // end right_bit_shift
