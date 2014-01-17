#include <cstdio>
#include <string.h>
#include <getopt.h>
#include <cstdlib>

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Generate random password and write to stdout.\n\n"
"   --len    NUM    make the password NUM chars.  Defaults to %lu\n"
"   --help          show this message and exit.\n";

static const char* chars = "abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@#";
/* NOTE: if each byte from /dev/random is uniform, then so is the residue
 * mod k, whenever k|256.  So we can simply sample as many bytes as there
 * are characters and use the low order bits.
 * */

#define ALPHABITS 6 /* chars should have length 2**ALPHABITS */
#define MAXLEN 64

int main(int argc, char *argv[]) {
	// define long options
	size_t len = 12;
	static struct option long_opts[] = {
		{"help",     no_argument,       0, 'h'},
		{"len",      required_argument, 0, 'l'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "hc:", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'h':
				printf(usage,argv[0],len);
				return 0;
			case 'l':
				len = atol(optarg);
				if (len > MAXLEN) {
					fprintf(stderr, "warning: maxlen (%i) exceeded.", MAXLEN);
					fprintf(stderr, "  setting len to %i\n", MAXLEN);
					len = MAXLEN;
				}
				break;
			case '?':
				printf(usage,argv[0],len);
				return 1;
		}
	}

	char word[MAXLEN+1];
	word[len] = 0;
	const int LMASK = (1 << ALPHABITS) - 1;
	FILE* f = fopen("/dev/urandom","rb");
	fread(word,1,len,f);
	fclose(f);
	for (size_t i = 0; i < len; i++) {
		word[i] = chars[word[i] & LMASK];
	}
	printf("%s\n",word);
	memset(word,0,len); /* clear memory on stack */

	return 0;
}
