/* See LICENSE file for copyright and license terms. */

/*
 * padding.c: implementation of functions related to the zero padding
 * section in the EPAI format.
 */


#include "../common.h"
#include "../epai.h"


extern void epai_padding_free_struct(epai_padding_section_t* ssp) {
	free(ssp);
}

extern epai_error_t epai_padding_new_struct(epai_padding_section_t** ssp) {
	epai_padding_section_t* ns = malloc(sizeof(*ns));
	if (ns == NULL) {
		epai_set_error("Could not allocate memory for new padding struct.");
		return EPAI_ERROR_MALLOC;
	}

	ns->type = EPAI_SECTION_PADDING;
	ns->length = 5;

	*ssp = ns;

	return EPAI_SUCCESS;
}


extern epai_error_t epai_padding_validate_blob(const epai_byte_t* buffer, uint32_t len) {
	int i;

	epai_error_t err = epai_validate_optional_section_blob(buffer, len);

	if (err != EPAI_SUCCESS) {
		return err;
	}

	if (*buffer != EPAI_SECTION_PADDING) {
		epai_set_error("Could not validate section blob: "
				"section type code byte is not Padding.");
		return EPAI_ERROR_SECTION_TYPE;
	}

	for (i = 5; i < len; ++i) {
		if (buffer[i] != 0) {
			epai_set_error("Invalid section blob: nonzero padding.");
			return EPAI_ERROR_NONZERO_PADDING;
		}
	}

	return EPAI_SUCCESS;
}


extern epai_error_t epai_padding_parse_blob(epai_padding_section_t** ssp,
		epai_file_t* file, const epai_byte_t* buffer, uint32_t len) {
	epai_error_t err = epai_padding_validate_blob(buffer, len);
	epai_padding_section_t* ns;

	if (err != EPAI_SUCCESS) {
		return err;
	}

	err = epai_padding_new_struct(&ns);
	if (err != EPAI_SUCCESS) {
		return err;
	}

	ns->length = len;

	*ssp = ns;

	return EPAI_SUCCESS;
}


extern uint32_t epai_padding_parse_length(const epai_file_t* file,
		const epai_byte_t* buffer) {
	switch (file->endian) {
	case EPAI_ENDIAN_LITTLE:
		return le32toh(*(uint32_t*)(buffer + 1) + 5);
	case EPAI_ENDIAN_BIG:
		return be32toh(*(uint32_t*)(buffer + 1) + 5);
	default:
		return *(uint32_t*)(buffer + 1) + 5;
	}
}

extern uint32_t epai_padding_encode_length(const epai_padding_section_t* ssp) {
	return ssp->length;
}


extern epai_error_t epai_padding_fill_blob(const epai_padding_section_t* ssp,
		const epai_file_t* file, epai_byte_t* buffer, uint32_t len) {
	int i;

	if (ssp->length < 5 || len != ssp->length) {
		epai_set_error("Padding must be at least 5 bytes long.");
		return EPAI_ERROR_SECTION_LENGTH;
	}

	if (len < ssp->length) {
		epai_set_error("Cannot fill buffer with padding blob: "
				"buffer too short.");
		return EPAI_ERROR_SECTION_LENGTH;
	}

	*buffer = EPAI_SECTION_PADDING;

	switch (file->endian) {
	case EPAI_ENDIAN_NATIVE:
		*(uint32_t*) (buffer + 1) = ssp->length - 5;
		break;
	case EPAI_ENDIAN_LITTLE:
		*(uint32_t*) (buffer + 1) = htole32(ssp->length - 5);
		break;
	case EPAI_ENDIAN_BIG:
		*(uint32_t*) (buffer + 1) = htobe32(ssp->length - 5);
		break;
	}

	for (i = 5; i < ssp->length; ++i) {
		buffer[i] = 0;
	}

	return EPAI_SUCCESS;
}

extern epai_error_t epai_padding_new_blob(const epai_padding_section_t* ssp,
		const epai_file_t* file, epai_byte_t** out, uint32_t* len) {
	epai_byte_t* r = malloc(ssp->length);
	epai_error_t err;

	if (r == NULL) {
		epai_set_error("Could not allocate memory for new padding blob.");
		err = EPAI_ERROR_MALLOC;
	} else {
		err = epai_padding_fill_blob(ssp, file, r, ssp->length);
		if (err == EPAI_SUCCESS) {
			*out = r;
			*len = ssp->length;
		} else {
			free(r);
		}
	}

	return err;
}
