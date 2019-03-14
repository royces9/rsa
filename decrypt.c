#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_READ 64
#define BYTE_SIZE 8

struct key {
	uint64_t modulus;
	uint64_t exponent;
};

struct key get_key(char *file);
uint32_t mod_exp(uint32_t b, uint32_t e, uint32_t m);

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

	for(uint32_t buff = 0, r = read(input, &buff, sizeof(buff)); r; r = read(input, &buff, sizeof(buff))) {
		uint32_t out = mod_exp(buff, e, n);

		write(output, &out, sizeof(out));
	}

	return 0;
}


uint32_t mod_exp(uint32_t b, uint32_t e, uint32_t m) {
	if(m == 1)
		return 0;

	uint32_t c = 1;
	for(int ep = 0; ep < e; ++ep) {
		c = (c * b) % m;
	}

	return c;
}


struct key get_key(char *file) {
	FILE *fp = fopen(file, "r");
	char temp[MAX_READ];

	struct key key;

	fgets(temp, MAX_READ, fp);
	key.modulus = strtol(temp, NULL, 16);
	
	memset(temp, 0, MAX_READ);

	fgets(temp, MAX_READ, fp);
	key.exponent = atoi(temp);
	
	fclose(fp);

	return key;
}
