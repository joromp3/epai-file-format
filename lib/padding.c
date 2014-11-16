/* See LICENSE file for copyright and license terms. */

/*
 * padding.c: implementation of functions related to the zero padding
 * section in the EPAI format.
 */


#include "common.h"
#include "epai.h"


extern epai_error_t epai_validate_padding_blob(const char* buffer,
					       uint32_t len) {
	int i;

	epai_error_t error = epai_validate_optional_section_blob(buffer, len);

	if (error) {
		return error;
	}

	if (*buffer != EPAI_SECTION_PADDING) {
		return EPAI_ERROR_SECTION_TYPE;
	}

	for (i = 5; i < len; ++i) {
		if (buffer[i] != 0) {
			return EPAI_ERROR_NONZERO_PADDING;
		}
	}

	return EPAI_SUCCESS;
}

static epai_error_t epai_fill_padding_blob(char* buffer,
					   const epai_padding_section_t* ssp) {
	int i;

	if (ssp->length < 5) {
		return EPAI_ERROR_SECTION_LENGTH;
	}

	*buffer = EPAI_SECTION_PADDING;

	*(uint32_t*)(buffer + 1) = ssp->length - 5;

	for (i = 5; i < ssp->length; ++i) {
		buffer[i] = 0;
	}

	return EPAI_SUCCESS;
}

extern epai_error_t epai_new_padding_blob(const epai_padding_section_t* ssp,
					  char** out, uint32_t* len) {
	char* r = malloc(ssp->length);
	epai_error_t error;

	if (r == NULL) {
		error = EPAI_ERROR_MALLOC;
	} else {
		error = epai_fill_padding_blob(r, ssp);
		if (error == EPAI_SUCCESS) {
			*out = r;
			*len = ssp->length;
		} else {
			free(r);
		}
	}

	return error;
}
