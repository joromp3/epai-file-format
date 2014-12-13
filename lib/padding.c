/* See LICENSE file for copyright and license terms. */

/*
 * padding.c: implementation of functions related to the zero padding
 * section in the EPAI format.
 */


#include "common.h"
#include "epai.h"


extern void epai_padding_free_struct(epai_padding_section_t* ssp) {
	free(ssp);
}

extern epai_error_t epai_padding_new_struct(epai_padding_section_t** ssp) {
	*ssp = malloc(sizeof(**ssp));
	if (*ssp == NULL) {
		return EPAI_ERROR_MALLOC;
	}

	(*ssp)->type = EPAI_SECTION_PADDING;
	(*ssp)->length = 5;

	return EPAI_SUCCESS;
}


extern epai_error_t epai_padding_validate_blob(const char* buffer, uint32_t len) {
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


extern epai_error_t epai_padding_parse_blob(epai_padding_section_t** ssp,
		const char* buffer, uint32_t len) {
	epai_error_t error = epai_padding_validate_blob(buffer, len);

	if (error) {
		return error;
	}

	error = epai_padding_new_struct(ssp);
	(*ssp)->length = len;

	if (error) {
		return error;
	}

	return EPAI_SUCCESS;
}


extern uint32_t epai_padding_parse_length(const char* buffer) {
	/* FIXME endian */
	return *(uint32_t*)(buffer + 1);
}

extern uint32_t epai_padding_encode_length(const epai_padding_section_t* ssp) {
	return ssp->length;
}


extern epai_error_t epai_padding_fill_blob(const epai_padding_section_t* ssp,
		char* buffer, uint32_t len) {
	int i;

	if (ssp->length < 5 || len != ssp->length) {
		return EPAI_ERROR_SECTION_LENGTH;
	}

	*buffer = EPAI_SECTION_PADDING;

	/* FIXME handle endian */
	*(uint32_t*) (buffer + 1) = ssp->length - 5;

	for (i = 5; i < ssp->length; ++i) {
		buffer[i] = 0;
	}

	return EPAI_SUCCESS;
}

extern epai_error_t epai_padding_new_blob(const epai_padding_section_t* ssp,
		char** out, uint32_t* len) {
	char* r = malloc(ssp->length);
	epai_error_t error;

	if (r == NULL) {
		error = EPAI_ERROR_MALLOC;
	} else {
		error = epai_padding_fill_blob(ssp, r, ssp->length);
		if (error == EPAI_SUCCESS) {
			*out = r;
			*len = ssp->length;
		} else {
			free(r);
		}
	}

	return error;
}
