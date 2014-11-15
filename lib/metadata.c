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
	size_t keylen, vallen;

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

		/* Skip to next key and decrement len. */
		buffer += ++keylen;
		vallen = strlen(buffer);
		buffer += ++vallen;
		len -= keylen + vallen;
	} while (len > 5);

	if (len != 5) { /* overread: last string ends past len. */
		return EPAI_ERROR_SECTION_LENGTH;
	}

	return EPAI_SUCCESS;
}
