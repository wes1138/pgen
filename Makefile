main = pgen
CC = g++
CFLAGS = -march=native -O2 -Wall -std=c++0x
LDADD =
LDFLAGS =

$(main) : pgen.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDADD)

.PHONY : clean
clean :
	rm -f $(main)
