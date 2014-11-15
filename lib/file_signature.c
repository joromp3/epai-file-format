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


extern epai_error_t epai_validate_file_signature(const char* buffer,
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
	    *++buffer != 0x49 || *++buffer != 0x0d ||
	    *++buffer != 0x0a || *++buffer != 0x0a) {
		return EPAI_ERROR_BAD_FILE_SIGNATURE;
	}

	if (*++buffer > max_format_version) {
		return EPAI_ERROR_VERSION_UNSUPPORTED;
	}

	endian_marker = *++buffer;
	endian_marker |= *++buffer << 8;

	if (!(endian_marker == 0xAF00 || endian_marker == 0x00AF)) {
		return EPAI_ERROR_BAD_FILE_SIGNATURE;
	}

	return EPAI_SUCCESS;
}

