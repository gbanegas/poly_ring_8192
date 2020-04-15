/*
 * poly_r_8096.c
 *
 *  Created on: Apr 14, 2020
 *      Author: yoda
 */

#include "poly_r_8192.h"

poly* create_polynomial() {
	poly *polynomial = (poly*) calloc(1, sizeof(poly));
	return polynomial;
}

void set_pos(int pos, poly *polynomial) {
	element_p one = 1;
	int idx_block = pos / 64;
	int idx_pos = 64 - ((idx_block * 64) - pos);
	polynomial->coeffs[idx_block] = polynomial->coeffs[idx_block]
			| (one << idx_pos);

}

void flip_pos(int pos, poly *polynomial) {
	element_p one = 1;
	int idx_block = pos / 64;
	int idx_pos = 64 - ((idx_block * 64) - pos);

	polynomial->coeffs[idx_block] = (polynomial->coeffs[idx_block]
			^ (one << idx_pos));

}

void add_poly(poly *result, const poly *p1, const poly *p2) {

	for (int i = 0; i < 128; i++) {
		result->coeffs[i] = p1->coeffs[i] ^ p2->coeffs[i];
	}
}

long toomspace(unsigned long n) {
	return 5 * n + 30;
}

long toomuspace(unsigned long sa) {
	return 2 * sa + 32 + toomspace(sa / 4 + 4);
}

int gf_mul_r(unsigned long *c, const unsigned long *a, unsigned long sa,
		const unsigned long *b, unsigned long sb) {
	int rc = 0;
	unsigned long sc = sa + sb;
	/* As a starting guess, assume that c may alias a or b */
	unsigned long *dst = c;
	mul_pool_t xxpool;
	struct mul_pool *xpool = NULL;

	unsigned long sp, sp2;
	sp = toomspace(sa); // Space for balanced TC routines

	if (sa != sb) {
		sp2 = toomuspace(2 * sa); // Space for unbalanced TC routines
		if (sp < sp2)
			sp = sp2; /* worst-case required */
		sp2 = 2 * sa + toomspace(sa); // Space for unbalanced TC routines w/ lazy cut
		if (sp < sp2)
			sp = sp2; /* worst-case required */
	}

	memset(xxpool, 0, sizeof(mul_pool_t));
	xpool = xxpool;

	if (xpool->stk_size < sp) {
		void *p = realloc(xpool->stk, sp * sizeof(unsigned long));
		if (p == NULL) {
			rc = -1;
			goto end_of_gf2x_mul_r;
		}
		xpool->stk = p;
		xpool->stk_size = sp;
	}

	// Avoid copy in common case
	gf_mul_kara(dst, a, b, sa, xpool->stk);

	end_of_gf2x_mul_r:
	//gf2x_mul_pool_clear(xxpool);

	if (dst && dst != c) {
		/* Then we have allocated a temp buffer */
		memcpy(c, dst, sc * sizeof(unsigned long));
		free(dst);
	}
	return rc;
}

void mul_poly(poly *result, const poly *p1, const poly *p2) {
	unsigned long r_tmp[256] = { 0 };
	gf_mul_r(r_tmp, p1->coeffs, 128, p2->coeffs, 128);
	for (int i = 0; i < 128; i++) {
		result->coeffs[i] = r_tmp[i] ^ r_tmp[i + 128];
	}

}

void div_poly(poly *result, const poly p1, const poly *p2) {

}

unsigned long long pop_count(const poly *p) {

	return 0;

}

void print_polynomial(poly *polynomial) {

	int idx = 0;
	element_p one = 1;
	for (int i = 0; i < 128; i++) {
		for (element_p j = 0; j < 64; j++) {
			element_p result = (one << j);
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

/*void gf2x_mul_kara(unsigned long *c, const unsigned long *a,
 const unsigned long *b, long n, unsigned long *stk) {
 unsigned long t;
 unsigned long *aa, *bb, *cc;
 long j, d, n2;

 assert(c != a);
 assert(c != b);

 #if 0
 if (n <= 0)
 {				 if turned on this test shows that calls with n == 0
 do occur (e.g from tunefft, FFT(19683)), but don't
 seem to be harmful if mul_basecase_n just returns.
 printf("\nWarning: n %ld in call to KarMul\n", n);
 fflush(stdout);
 }
 #endif

 if (n < 10) {
 gf_mul_basecase(c, a, n, b, n);
 return;
 }

 n2 = (n + 1) / 2;  ceil(n/2)
 d = n & 1;  2*n2 - n = 1 if n odd, 0 if n even
 aa = stk;  Size n2
 bb = aa + n2;  Size n2
 cc = bb + n2;  Size n2

 stk = cc + n2;  sp(n) = 3*ceil(n/2)) + sp(ceil(n/2))

 const unsigned long *a1 = a + n2;  a[n2]
 const unsigned long *b1 = b + n2;  b[n2]
 unsigned long *c1 = c + n2;  c[n2]
 unsigned long *c2 = c1 + n2;  c[2*n2]
 unsigned long *c3 = c2 + n2;  c[3*n2]

 gf2x_mul_kara(c, a, b, n2, stk);  Low
 gf2x_mul_kara(c2, a1, b1, n2 - d, stk);  High

 for (j = 0; j < n2 - d; j++) {
 aa[j] = a[j] ^ a1[j];
 bb[j] = b[j] ^ b1[j];
 cc[j] = c1[j] ^ c2[j];
 }
 for (; j < n2; j++) {  Only when n odd
 aa[j] = a[j];
 bb[j] = b[j];
 cc[j] = c1[j] ^ c2[j];
 }

 gf2x_mul_kara(c1, aa, bb, n2, stk);  Middle

 for (j = 0; j < n2 - 2 * d; j++) {
 t = cc[j];
 c1[j] ^= t ^ c[j];
 c2[j] ^= t ^ c3[j];
 }
 for (; j < n2; j++) {  Only when n odd
 c1[j] ^= cc[j] ^ c[j];
 c2[j] ^= cc[j];
 }
 }*/
