/* See LICENSE file for copyright and license terms. */

/*
 * file_signature.c: implementation of functions related to the file
 * signature section in the EPAI format.
 */


#include "common.h"
#include "epai.h"


/* According to spec, all file signatures must be of exactly this length. */
static const int file_signature_header_len = 11;


/* Refuse to accept file signature headers with format version > this. */
static int max_format_version = 0x00;


static epai_error_t epai_new_file_signature_struct(epai_fsign_section_t** ssp) {
	*ssp = malloc(sizeof(**ssp));
	if (*ssp == NULL) {
		return EPAI_ERROR_MALLOC;
	}

	(*ssp)->type = EPAI_SECTION_PADDING;

	return EPAI_SUCCESS;
}


extern epai_error_t epai_validate_file_signature_blob(const char* buffer,
						      uint32_t len) {
	unsigned int endian_marker;

	if (len != file_signature_header_len) {
		return EPAI_ERROR_SECTION_LENGTH;
	}

	if (*buffer != EPAI_SECTION_FILE_SIGNATURE) {
		return EPAI_ERROR_SECTION_TYPE;
	}

	if (*++buffer != 'E' || *++buffer != 'P' ||
	    *++buffer != 'A' || *++buffer != 'I' ||
	    *++buffer != 0x0d || *++buffer != 0x0a || *++buffer != 0x0a) {
		return EPAI_ERROR_BAD_FILE_SIGNATURE;
	}

	if (*++buffer > max_format_version) {
		return EPAI_ERROR_VERSION_UNSUPPORTED;
	}

	endian_marker = *++buffer;
	endian_marker |= *++buffer << 8;

	/* Validation should pass regardless of file endian. */
	if (!(endian_marker == 0xAF00 || endian_marker == 0x00AF)) {
		return EPAI_ERROR_BAD_FILE_SIGNATURE;
	}

	return EPAI_SUCCESS;
}


extern epai_error_t epai_parse_file_signature_blob(epai_fsign_section_t** ssp,
		const char* buffer) {
	epai_error_t error = epai_validate_file_signature_blob(buffer,
			file_signature_header_len);

	if (error) {
		return error;
	}

	error = epai_new_file_signature_struct(ssp);

	if (error) {
		return error;
	}

	return EPAI_SUCCESS;
}


static epai_error_t epai_fill_file_signature_blob(char* buffer) {
	*buffer = EPAI_SECTION_FILE_SIGNATURE;
	*++buffer = 'E';
	*++buffer = 'P';
	*++buffer = 'A';
	*++buffer = 'I';
	*++buffer = 0x0D;
	*++buffer = 0x0A;
	*++buffer = 0x0A;
	*++buffer = 0x00; /* TODO: get a version value from global state. */
	/* FIXME: detect and set the correct endian marker. */
	*++buffer = 0x00;
	*++buffer = 0xAF;

	return EPAI_SUCCESS;
}

extern epai_error_t epai_new_file_signature_blob(const epai_fsign_section_t* ssp,
					  char** out, uint32_t* len) {
	char* r = malloc(file_signature_header_len);
	epai_error_t error;

	if (r == NULL) {
		error = EPAI_ERROR_MALLOC;
	} else {
		error = epai_fill_file_signature_blob(r);
		if (error == EPAI_SUCCESS) {
			*out = r;
			*len = file_signature_header_len;
		} else {
			free(r);
		}
	}

	return error;
}
