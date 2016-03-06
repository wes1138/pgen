main = pgen
CC = gcc
CFLAGS = -march=native -O2 -Wall
LDADD =
LDFLAGS =

$(main) : pgen.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDADD)

.PHONY : clean
clean :
	rm -f $(main)
