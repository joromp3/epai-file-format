/* See LICENSE file for copyright and license terms. */

/* main.c: executable main function for epaipoke. */


#include "../lib/common.h"
#include "../lib/epai.h"


static void get_endian(const epai_file_t* efp) {
	switch (efp->endian) {
	case EPAI_ENDIAN_BIG:
		printf("Endian: BIG.\n");
		break;
	case EPAI_ENDIAN_LITTLE:
		printf("Endian: LITTLE.\n");
		break;
	}
}

static void get_version(const epai_file_t* efp) {
	printf("Format version code: 0x%X.\n", efp->version);
}

static epai_error_t decode_file(const char* path, epai_file_t** efp) {
	/* must load into memory until library implements file i/o */
	FILE* fp = NULL;
	size_t flen, rlen;
	char* data;
	epai_error_t err;
	epai_decoder_t* ds;

	fp = fopen(path, "r");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file.\n");
		return EPAI_ERROR_FILEIO;
	}

	fseek(fp, 0, SEEK_END);
	flen = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	data = malloc(flen);
	if (data == NULL) {
		fclose(fp);
		fprintf(stderr, "Failed to allocate memory for decoding.\n");
		return EPAI_ERROR_MALLOC;
	}

	rlen = fread(data, 1, flen, fp);
	if (rlen != flen) {
		fclose(fp);
		free(data);
		fprintf(stderr, "Failed to read file into memory.\n");
		return EPAI_ERROR_FILEIO;
	}

	fclose(fp);

	err = epai_decoder_new_from_ptr(&ds, data, flen);
	if (err) {
		free(data);
		fprintf(stderr, "Failed to initialize decoder. Error %d. "
				"libepai error:\n%s\n", err, epai_get_error());
		return err;
	}

	err = epai_decoder_decode(ds);
	if (err) {
		free(data);
		fprintf(stderr, "Failed to decode buffer. Error %d. "
				"libepai error:\n%s\n", err, epai_get_error());
		return err;
	}

	*efp = ds->file;

	return EPAI_SUCCESS;
}

static epai_error_t encode_file(const char* path, const epai_file_t* efp) {
	/* TODO use library to encode */
	fprintf(stderr, "ENCODING UNIMPLEMENTED\n");
	return EPAI_ERROR_BAD_OPERATION;
}


static int get_value(const char* path, const char* var) {
	epai_file_t* efp;
	epai_error_t err = decode_file(path, &efp);
	if (err) {
		fprintf(stderr, "Failed to decode file. Error %d. "
				"libepai error:\n%s\n", err, epai_get_error());
		return 2;
	}

	if (!strcmp(var, "all")) {
		get_endian(efp);
		get_version(efp);
	} else if (!strcmp(var, "endian")) {
		get_endian(efp);
	} else if (!strcmp(var, "fver")) {
		get_version(efp);
	} else {
		fprintf(stderr, "Invalid variable name.\n");
		return 8;
	}

	return 0;
}

static int set_value(const char* path, const char* var, const char* val) {
	epai_file_t* efp;
	epai_error_t err = decode_file(path, &efp);
	if (err) {
		fprintf(stderr, "Failed to decode file. Error %d.\n", err);
		return 2;
	}

	err = encode_file(path, efp);
	if (err) {
		fprintf(stderr, "Failed to encode file. Error %d.\n", err);
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

