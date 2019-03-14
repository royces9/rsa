CC=gcc


all:
	$(CC) getkey.c -o getkey
	$(CC) rsa.c -o rsa

clean:
	del encrypt decrypt getkey
