buff_t mod_exp(buff_t b, uint32_t e, uint32_t m) {
	if(m == 1)
		return 0;

	buff_t c = 1;
	for(int ep = 0; ep < e; ++ep) {
		c = (c * b) % m;
	}

	return c;
}
