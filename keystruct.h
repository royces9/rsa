#define MAX_READ 64

struct key {
	uint64_t modulus;
	uint64_t exponent;
};


struct key get_key(char *file) {
	FILE *fp = fopen(file, "r");
	char temp[MAX_READ];

	struct key key;

	fgets(temp, MAX_READ, fp);
	key.modulus = strtol(temp, NULL, 16);

	memset(temp, 0, MAX_READ);

	fgets(temp, MAX_READ, fp);
	key.exponent = strtol(temp, NULL, 16);

	fclose(fp);

	return key;
}
