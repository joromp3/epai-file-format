/* See LICENSE file for copyright and license terms. */

/* main.c: executable main function for epaipoke. */


#include "../lib/common.h"
#include "../lib/epai.h"


static epai_error_t decode_file(const char* path, epai_file_t** efp) {
	/* TODO load and use library to decode */
	fprintf(stderr, "DECODING UNIMPLEMENTED\n");
	return NULL;
}

static epai_error_t encode_file(const char* path, const epai_file_t* efp) {
	/* TODO use library to encode */
	fprintf(stderr, "ENCODING UNIMPLEMENTED\n");
	return NULL;
}


static int get_value(const char* path, const char* var) {
	epai_file_t* efp;
	epai_error_t err = decode_file(path, &efp);
	if (err) {
		fprintf(stderr, "Failed to decode file.\n");
		return 2;
	}

	return 0;
}

static int set_value(const char* path, const char* var, const char* val) {
	epai_file_t* efp;
	epai_error_t err = decode_file(path, &efp);
	if (err) {
		fprintf(stderr, "Failed to decode file.\n");
		return 2;
	}

	if (encode_file(path, efp)) {
		fprintf(stderr, "Failed to encode file.\n");
		return 4;
	}

	return 0;
}


static void print_help(const char* progname) {
	printf("Usage:\n"
	       "print details about a file: `%s get <filename> all`\n"
	       "print a specific value:     `%s get <filename> <var>`\n"
	       "change a specific value:    `%s set <filename> <var> <val>`\n",
		progname, progname, progname);
}


int main(int argc, char** argv) {
	if (argc < 2) {
		print_help(argv[0]);
		return 1;
	}

	if (!strcmp(argv[1], "get")) {
		if (argc < 4) {
			print_help(argv[0]);
			return 1;
		} else {
			return get_value(argv[2], argv[3]);
		}
	}

	if (!strcmp(argv[1], "set")) {
		if (argc < 5) {
			print_help(argv[0]);
			return 1;
		} else {
			return set_value(argv[2], argv[3], argv[4]);
		}
	}

	print_help(argv[0]);
	return 1;
}

