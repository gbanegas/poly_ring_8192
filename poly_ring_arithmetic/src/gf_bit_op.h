/*
 * gf_bit_op.h
 *
 *  Created on: Apr 15, 2020
 *      Author: yoda
 */

#ifndef GF_BIT_OP_H_
#define GF_BIT_OP_H_

#include <x86intrin.h>
#include <avx2intrin.h>
#include <immintrin.h>
#include <stdalign.h>

#include "export.h"
void rotate_bit_right(element_p in[]);
void right_bit_shift(const int length, element_p in[]);

void left_bit_shift(const int length, element_p in[]);
void rotate_bit_left(element_p in[]);

void shift_n_bits_to_right(int amount, element_p *in);

#endif /* GF_BIT_OP_H_ */
