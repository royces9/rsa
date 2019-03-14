#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "keystruct.h"
#include "modexp.h"

#define MAX_READ 64
#define BYTE_SIZE 8


int main(int argc, char **argv) {
	if(argc != 3) {
		puts("Two arguments required: file, key.");
		return 0;
	}

	struct key key = get_key(argv[2]);
	uint64_t n = key.modulus;
	uint64_t e = key.exponent;

	int input = open(argv[1], O_RDONLY);

	char *out_f = malloc( (strlen(argv[1]) + 5) * sizeof(*out_f));
	strcpy(out_f, argv[1]);
	strcat(out_f, ".dcr");
	int output = open(out_f, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	;
	for(uint32_t buff = 0, r = 0;  r = read(input, &buff, sizeof(buff)); ) {
		uint32_t out = mod_exp(buff, e, n);

		write(output, &out, sizeof(out));
	}

	return 0;
}
