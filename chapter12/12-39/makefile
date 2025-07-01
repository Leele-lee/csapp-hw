CC = gcc
CFLAGS = -m64 -pthread

all:
	$(CC) $(CFLAGS) proxy.c ../csapp.c -o proxy

test:

.PHONY : clean
clean:
	find . -type f -executable -print0 | xargs -0 rm -f --



