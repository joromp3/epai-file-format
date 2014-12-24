/* See LICENSE file for copyright and license terms. */

/* main.c: executable main function for epaipoke. */


static void print_help(const char* progname) {
	printf("Usage:\n"
	       "print details about a file: `%s get <filename> all`\n"
	       "print a specific value:     `%s get <filename> <var>`\n"
	       "change a specific value:    `%s set <filename> <var> <val>`\n",
		progname, progname, progname);
}


static int check_usage(int argc, char** argv) {
	if (argc < 2) {
		print_help(argv[0]);
		return 0;
	}

	if (!strcmp(argv[1], "get")) {
		if (argc < 4) {
			print_help(argv[0]);
			return 0;
		} else {
			return 1;
		}
	}

	if (!strcmp(argv[1], "set")) {
		if (argc < 5) {
			print_help(argv[0]);
			return 0;
		} else {
			return 1;
		}
	}

	print_help(argv[0]);
	return 0;
}


int main(int argc, char** argv) {
	if (!check_usage(argc, argv)) {
		return 1;
	}
	return 0;
}

