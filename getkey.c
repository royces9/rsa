#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct key {
	uint64_t modulus;
	uint64_t exponent;
};

uint64_t lambda(uint64_t p, uint64_t q) {
	--p;
	--q;

	uint64_t out = 0;

	uint64_t larger;
	uint64_t smaller;

	if(p > q) {
		larger = p;
		smaller = q;
	} else {
		larger = q;
		smaller = p;
	}


	for(uint64_t i = larger; larger % smaller; larger += i);

	return larger;
}

uint64_t mod_mult_inv(uint64_t a, uint64_t m) {
	for(uint64_t n = m; ((m + 1) % a) != 0; m += n);

	return (m + 1) / a;
}


void print_key(struct key *a) {
	printf("%x\n", a->modulus);
	printf("%x\n", a->exponent);
}


int main(int argc, char **argv) {
	if(argc != 4) {
		puts("3 args required: p, q, e");
		return 1;
	}
	
	uint64_t p = atoi(argv[1]);
	uint64_t q = atoi(argv[2]);
	uint64_t e = atoi(argv[3]);
	
	uint64_t n = p * q;
	uint64_t ln = lambda(p, q);
	uint64_t d = mod_mult_inv(e, ln);

	struct key public = {n, e};
	struct key private = {n, d};

	puts("Public");
	print_key(&public);

	puts("Private");
	print_key(&private);
	return 0;
}
