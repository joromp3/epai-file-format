/* See LICENSE file for copyright and license terms. */

/*
 * metadata.c: implementation of functions related to the text metadata
 * section in the EPAI format.
 */


#include "common.h"
#include "epai.h"


static int validate_key_string(const char* key, uint32_t len) {
	int i;

	for (i = 0; i < len; ++i) {
		if (!((key[i] >= 'a' && key[i] <= 'z') ||
		      (key[i] >= 'A' && key[i] <= 'Z'))) {
			return 0;
		}
	}

	return 1;
}

extern epai_error_t epai_validate_metadata_blob(const char* buffer,
						uint32_t len) {
	uint32_t keylen, vallen, npairs = 0;

	epai_error_t error = epai_validate_optional_section_blob(buffer, len);

	if (error) {
		return error;
	}

	if (*buffer != EPAI_SECTION_METADATA) {
		return EPAI_ERROR_SECTION_TYPE;
	}

	/* Start at location 5 and loop until reaching len. */
	buffer += 5;
	do {
		keylen = strlen(buffer);

		if (!validate_key_string(buffer, keylen)) {
			return EPAI_ERROR_METADATA_KEY;
		}

		if (keylen >= EPAI_METADATA_KEY_LEN) {
			return EPAI_ERROR_METADATA_LIMITS;
		}

		buffer += ++keylen;
		vallen = strlen(buffer);

		if (vallen >= EPAI_METADATA_VAL_LEN) {
			return EPAI_ERROR_METADATA_LIMITS;
		}

		buffer += ++vallen;
		len -= keylen + vallen;

		++npairs;
	} while (len > 5);

	if (len != 5) { /* overread: last string ends past len. */
		return EPAI_ERROR_SECTION_LENGTH;
	}

	if (npairs > EPAI_METADATA_MAX_PAIRS) {
		return EPAI_ERROR_METADATA_LIMITS;
	}

	return EPAI_SUCCESS;
}


static uint32_t epai_calculate_blob_length(const epai_metadata_section_t* ssp) {
	uint32_t l;
	int i;

	if (ssp->num_pairs > EPAI_METADATA_MAX_PAIRS) {
		return EPAI_ERROR_METADATA_LIMITS;
	}

	for (i = 0; i < ssp->num_pairs; ++i) {
		if (ssp->keylens[i] > EPAI_METADATA_KEY_LEN) {
			return EPAI_ERROR_METADATA_LIMITS;
		}

		l += ssp->keylens[i] + 1;

		if (ssp->vallens[i] > EPAI_METADATA_VAL_LEN) {
			return EPAI_ERROR_METADATA_LIMITS;
		}

		l += ssp->vallens[i] + 1;
	}

	return l + 5;
}


extern epai_error_t epai_new_metadata_blob(const epai_metadata_section_t* ssp,
					   char** out, uint32_t* len) {
	epai_error_t error;
	uint32_t l;
	char *r, *s;
	int i;

	l = epai_calculate_blob_length(ssp);

	r = malloc(l);
	if (r == NULL) {
		return EPAI_ERROR_MALLOC;
	} else {
		s = r;
	}

	*s = EPAI_SECTION_METADATA;
	*(uint32_t*)(s + 1) = l - 5;
	s += 5;

	for (i = 0; i < ssp->num_pairs; ++i) {
		strcpy(s, ssp->keys[i]);
		s += ssp->keylens[i] + 1;
		strcpy(s, ssp->values[i]);
		s += ssp->vallens[i] + 1;
	}
}


