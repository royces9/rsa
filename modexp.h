uint32_t mod_exp(uint32_t b, uint32_t e, uint32_t m) {
	if(m == 1)
		return 0;

	uint32_t c = 1;
	for(int ep = 0; ep < e; ++ep) {
		c = (c * b) % m;
	}

	return c;
}
