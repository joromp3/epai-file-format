/* See LICENSE file for copyright and license terms. */

/*
 * file_signature.c: implementation of functions related to the zero
 * padding section in the EPAI format.
 */


#include "common.h"
#include "epai.h"


extern epai_error_t epai_validate_padding(const char* buffer, uint32_t len) {
	uint32_t inner_len;
	int i;

	if (len < 5) {
		return EPAI_ERROR_SECTION_LENGTH;
	}

	if (*buffer != EPAI_SECTION_PADDING) {
		return EPAI_ERROR_SECTION_TYPE;
	}

	/* FIXME: handle endian properly. */
	inner_len = *(uint32_t*)(buffer + 1);

	if (len != inner_len + 5) {
		return EPAI_ERROR_SECTION_LENGTH;
	}

	for (i = 5; i < len; ++i) {
		if (buffer[i] != 0) {
			return EPAI_ERROR_NONZERO_PADDING;
		}
	}

	return EPAI_SUCCESS;
}

extern epai_error_t epai_fill_padding(char* buffer, uint32_t len) {
	int i;

	if (len < 5) {
		return EPAI_ERROR_SECTION_LENGTH;
	}

	*buffer = EPAI_SECTION_PADDING;

	*(uint32_t*)(buffer + 1) = len - 5;

	for (i = 5; i < len; ++i) {
		buffer[i] = 0;
	}

	return EPAI_SUCCESS;
}

extern char* epai_new_padding(uint32_t len) {
	char* r = malloc(len);

	if (r != NULL) {
		if (epai_fill_padding(r, len)) {
			free(r);
		}
	}

	return r;
}
