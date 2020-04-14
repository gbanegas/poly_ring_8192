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
	poly *pol = create_polynomial();

	print_polynomia(pol);

	set_pos(4096, pol);
	set_pos(3, pol);
	set_pos(8, pol);
	set_pos(8095, pol);
	print_polynomia(pol);

	flip_pos(3,pol);
	flip_pos(5,pol);
	flip_pos(8,pol);
	flip_pos(100,pol);
	flip_pos(100,pol);
	print_polynomia(pol);
	puts("!!!finishing!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
