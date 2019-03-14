CC=gcc


all:
	$(CC) getkey.c -o getkey
	$(CC) encrypt.c -o encrypt
	$(CC) decrypt.c -o decrypt


clean:
	del encrypt decrypt getkey
