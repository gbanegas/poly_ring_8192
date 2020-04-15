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

int main(void) {
	puts("!!!Starting !!!"); /* prints !!!Hello World!!! */
	poly *p1 = create_polynomial();
	poly *p2 = create_polynomial();
	poly *result = create_polynomial();

	set_pos(1, p1);


	set_pos(2, p2);

	printf("poly 1: ");
	print_polynomial(p1);

	printf("poly 2: ");
	print_polynomial(p2);

	mul_poly(result, p1, p2);

	printf("result p1*p2: ");
	print_polynomial(result);

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
