/*
 ============================================================================
 Name        : poly_ring_arithmetic.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "poly_r_8192.h"
#include "gf_bit_op.h"

int main(void) {
	puts("!!!Starting !!!"); /* prints !!!Hello World!!! */
	poly *p1 = create_polynomial();
	poly *p2 = create_polynomial();
	poly *result = create_polynomial();
	poly *p3 = create_polynomial();

	set_pos(1, p1);

	set_pos(2, p2);

	set_pos(0, p3);
	set_pos(6, p3);
	set_pos(63, p3);
	set_pos(8191, p3);

	printf("poly 1: ");
	print_polynomial(p1);

	printf("poly 2: ");
	print_polynomial(p2);

	printf("poly 3: ");
	print_polynomial(p3);

	mul_poly(result, p1, p2);

	printf("result p1*p2: ");
	print_polynomial(result);

	unsigned long deg_p1 = get_deg(p1);
	unsigned long deg_p2 = get_deg(p2);
	unsigned long deg_r = get_deg(result);
	unsigned long deg_p = get_deg(p3);

	printf("deg_p1: %lu , deg_p2: %lu, deg_r: %lu deg_p:%lu \n", deg_p1, deg_p2,
			deg_r, deg_p);

	rotate_bit_left(p3->coeffs);

	printf("poly 3: ");
	print_polynomial(p3);

	shift_n_bits_to_right(1, p3->coeffs);

	printf("poly 3: ");
	print_polynomial(p3);
	//print_polynomia(pol);

	/*set_pos(4096, pol);
	 set_pos(3, pol);
	 set_pos(8, pol);
	 set_pos(8095, pol);
	 print_polynomia(pol);

	 flip_pos(3,pol);
	 flip_pos(5,pol);
	 flip_pos(8,pol);
	 flip_pos(100,pol);
	 flip_pos(100,pol);
	 print_polynomia(pol);*/
	puts("!!!finishing!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
