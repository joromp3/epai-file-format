/* See LICENSE file for copyright and license terms. */

/*
 * metadata.c: implementation of functions related to the text metadata
 * section in the EPAI format.
 */


#include "../common.h"
#include "../epai.h"


extern int epai_metadata_validate_key_string(const char* key, uint32_t len) {
	int i;

	for (i = 0; i < len; ++i) {
		if (!((key[i] >= 'a' && key[i] <= 'z') ||
		      (key[i] >= 'A' && key[i] <= 'Z'))) {
			return 0;
		}
	}

	return 1;
}


/* currently unused function but could be useful. */
extern epai_error_t epai_metadata_update_length(epai_metadata_section_t* ssp) {
	uint32_t l = 0;
	int i;

	if (ssp->num_pairs > EPAI_METADATA_MAX_PAIRS) {
		epai_set_error("Too many metadata pairs.");
		return EPAI_ERROR_METADATA_LIMITS;
	}

	for (i = 0; i < ssp->num_pairs; ++i) {
		if (ssp->keylens[i] > EPAI_METADATA_KEY_LEN) {
			epai_set_error("Metadata key too long.");
			return EPAI_ERROR_METADATA_LIMITS;
		}

		l += ssp->keylens[i] + 1;

		if (ssp->vallens[i] > EPAI_METADATA_VAL_LEN) {
			epai_set_error("Metadata value too long.");
			return EPAI_ERROR_METADATA_LIMITS;
		}

		l += ssp->vallens[i] + 1;
	}

	ssp->length = l + 5;

	return EPAI_SUCCESS;
}


extern void epai_metadata_free_struct(epai_metadata_section_t* ssp) {
	int i;
	if (ssp->keys != NULL) {
		for (i = 0; i < EPAI_METADATA_MAX_PAIRS; ++i) {
			if (ssp->keys[i] != NULL) {
				free(ssp->keys[i]);
			}
		}
		free(ssp->keys);
	}
	if (ssp->values != NULL) {
		for (i = 0; i < EPAI_METADATA_MAX_PAIRS; ++i) {
			if (ssp->values[i] != NULL) {
				free(ssp->values[i]);
			}
		}
		free(ssp->values);
	}
	free(ssp->keylens);
	free(ssp->vallens);
	free(ssp);
}

extern epai_error_t epai_metadata_new_struct(epai_metadata_section_t** ssp) {
	int i;
	epai_metadata_section_t* ns;

	ns = malloc(sizeof(*ns));
	if (ns == NULL) {
		epai_set_error("Could not allocate memory for new metadata struct.");
		return EPAI_ERROR_MALLOC;
	}

	ns->type = EPAI_SECTION_METADATA;
	ns->num_pairs = 0;
	ns->length = 5;

	ns->keylens = calloc(EPAI_METADATA_MAX_PAIRS, sizeof(int));
	ns->vallens = calloc(EPAI_METADATA_MAX_PAIRS, sizeof(int));
	ns->keys = calloc(EPAI_METADATA_MAX_PAIRS, sizeof(char*));
	ns->values = calloc(EPAI_METADATA_MAX_PAIRS, sizeof(char*));

	if (ns->keylens == NULL ||
	    ns->vallens == NULL ||
	    ns->keys == NULL ||
	    ns->values == NULL) {
		epai_set_error("Could not allocate memory for metadata arrays.");
		epai_metadata_free_struct(ns);
		return EPAI_ERROR_MALLOC;
	}

	for (i = 0; i < EPAI_METADATA_MAX_PAIRS; ++i) {
		ns->keys[i] = malloc(EPAI_METADATA_KEY_LEN);
		ns->values[i] = malloc(EPAI_METADATA_VAL_LEN);

		if (ns->keys[i] == NULL || ns->values[i] == NULL) {
			epai_set_error("Could not allocate memory for "
					"metadata string buffer.");
			epai_metadata_free_struct(ns);
			return EPAI_ERROR_MALLOC;
		}
	}

	*ssp = ns;
	return EPAI_SUCCESS;
}

extern epai_error_t epai_metadata_add_pair(epai_metadata_section_t* ssp,
		const char* key, const char* value) {
	int keylen = strlen(key);
	int vallen = strlen(value);

	if (keylen > EPAI_METADATA_KEY_LEN) {
		epai_set_error("Could not add new metadata pair: "
				"key too long.");
		return EPAI_ERROR_METADATA_LIMITS;
	}
	if (keylen == 0) {
		epai_set_error("Could not add new metadata pair: "
				"key is empty.");
		return EPAI_ERROR_METADATA_KEY;
	}
	if (vallen > EPAI_METADATA_VAL_LEN) {
		epai_set_error("Could not add new metadata pair: "
				"value too long.");
		return EPAI_ERROR_METADATA_LIMITS;
	}
	if (ssp->num_pairs >= EPAI_METADATA_MAX_PAIRS) {
		epai_set_error("Could not add new metadata pair: "
				"no space left in array.");
		return EPAI_ERROR_METADATA_LIMITS;
	}

	strncpy(ssp->keys[ssp->num_pairs], key, EPAI_METADATA_KEY_LEN);
	strncpy(ssp->values[ssp->num_pairs], value, EPAI_METADATA_VAL_LEN);
	ssp->keylens[ssp->num_pairs] = keylen;
	ssp->vallens[ssp->num_pairs] = vallen;
	++ssp->num_pairs;
	ssp->length += keylen + vallen + 2;

	return EPAI_SUCCESS;
}

extern epai_error_t epai_metadata_remove_pair_by_index(epai_metadata_section_t* ssp,
		int index) {
	char *tempk, *tempv;
	int i;

	if (index >= ssp->num_pairs ||
	    index < 0) {
		epai_set_error("Could not remove metadata pair: "
				"index invalid.");
		return EPAI_ERROR_METADATA_LIMITS;
	}

	ssp->length -= ssp->keylens[index] + ssp->vallens[index] + 2;

	/* Rotate pointers. */
	tempk = ssp->keys[index];
	tempv = ssp->values[index];
	for (i = index; i < ssp->num_pairs;++i) {
		ssp->keys[i] = ssp->keys[i+1];
		ssp->values[i] = ssp->values[i+1];
		ssp->keylens[i] = ssp->keylens[i+1];
		ssp->vallens[i] = ssp->vallens[i+1];
	}
	--ssp->num_pairs;
	ssp->keys[ssp->num_pairs] = tempk;
	ssp->values[ssp->num_pairs] = tempv;
	ssp->keylens[ssp->num_pairs] = 0;
	ssp->vallens[ssp->num_pairs] = 0;

	return EPAI_SUCCESS;
}


extern epai_error_t epai_metadata_validate_blob(const epai_byte_t* buffer,
		uint32_t len) {
	uint32_t keylen, vallen, npairs = 0;

	epai_error_t err = epai_validate_optional_section_blob(buffer, len);

	if (err != EPAI_SUCCESS) {
		return err;
	}

	if (*buffer != EPAI_SECTION_METADATA) {
		epai_set_error("Could not validate section blob: "
				"section type code byte is not Text Metadata.");
		return EPAI_ERROR_SECTION_TYPE;
	}

	/* Start at location 5 and loop until reaching len. */
	buffer += 5;
	do {
		keylen = strlen(buffer);

		if (!epai_metadata_validate_key_string(buffer, keylen)) {
			epai_set_error("Invalid section blob: "
					"metadata key contains prohibited characters.");
			return EPAI_ERROR_METADATA_KEY;
		}

		if (keylen >= EPAI_METADATA_KEY_LEN) {
			epai_set_error("Invalid section blob: "
					"metadata key too long.");
			return EPAI_ERROR_METADATA_LIMITS;
		}

		buffer += ++keylen;
		vallen = strlen(buffer);

		if (vallen >= EPAI_METADATA_VAL_LEN) {
			epai_set_error("Invalid section blob: "
					"metadata value too long.");
			return EPAI_ERROR_METADATA_LIMITS;
		}

		buffer += ++vallen;
		len -= keylen + vallen;

		++npairs;
	} while (len > 5);

	if (len != 5) { /* overread: last string ends past len. */
		epai_set_error("Failed to validate section blob: "
				"Section length in stream does not match.");
		return EPAI_ERROR_SECTION_LENGTH;
	}

	if (npairs > EPAI_METADATA_MAX_PAIRS) {
		epai_set_error("Invalid section blob: "
				"too many metadata pairs.");
		return EPAI_ERROR_METADATA_LIMITS;
	}

	return EPAI_SUCCESS;
}


extern epai_error_t epai_metadata_parse_blob(epai_metadata_section_t** ssp,
		epai_file_t* file, const epai_byte_t* buffer, uint32_t len) {
	epai_error_t err = epai_metadata_validate_blob(buffer, len);
	epai_metadata_section_t* ns;
	int kl, vl;

	if (err != EPAI_SUCCESS) {
		return err;
	}

	err = epai_metadata_new_struct(&ns);
	if (err != EPAI_SUCCESS) {
		return err;
	}

	buffer += 5;
	len -= 5;
	while (len > 0) {
		const epai_byte_t* vp;
		kl = strlen(buffer);
		vp = buffer + kl + 1;
		vl = strlen(vp);

		err = epai_metadata_add_pair(ns, buffer, vp);
		if (err != EPAI_SUCCESS) {
			epai_metadata_free_struct(ns);
			return err;
		}

		buffer = vp + vl + 1;
		len -= kl + vl + 2;
	}

	*ssp = ns;

	return EPAI_SUCCESS;
}


extern uint32_t epai_metadata_parse_length(const epai_file_t* file,
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

extern uint32_t epai_metadata_encode_length(const epai_metadata_section_t* ssp) {
	return ssp->length;
}


extern epai_error_t epai_metadata_fill_blob(const epai_metadata_section_t* ssp,
		const epai_file_t* file, epai_byte_t* out, uint32_t len) {
	int i;

	if (len < ssp->length) {
		epai_set_error("Cannot fill buffer with metadata blob: "
				"buffer too short.");
		return EPAI_ERROR_SECTION_LENGTH;
	}

	*out = EPAI_SECTION_METADATA;

	switch (file->endian) {
	case EPAI_ENDIAN_NATIVE:
		*(uint32_t*) (out + 1) = ssp->length - 5;
		break;
	case EPAI_ENDIAN_LITTLE:
		*(uint32_t*) (out + 1) = htole32(ssp->length - 5);
		break;
	case EPAI_ENDIAN_BIG:
		*(uint32_t*) (out + 1) = htobe32(ssp->length - 5);
		break;
	}

	out += 5;

	for (i = 0; i < ssp->num_pairs; ++i) {
		strcpy(out, ssp->keys[i]);
		out += ssp->keylens[i] + 1;
		strcpy(out, ssp->values[i]);
		out += ssp->vallens[i] + 1;
	}

	return EPAI_SUCCESS;
}

extern epai_error_t epai_metadata_new_blob(const epai_metadata_section_t* ssp,
		const epai_file_t* file, epai_byte_t** out, uint32_t* len) {
	epai_error_t err;
	epai_byte_t *r;

	r = malloc(ssp->length);
	if (r == NULL) {
		epai_set_error("Could not allocate memory for new metadata blob.");
		err = EPAI_ERROR_MALLOC;
	} else {
		err = epai_metadata_fill_blob(ssp, file, r, ssp->length);
		if (err == EPAI_SUCCESS) {
			*out = r;
			*len = ssp->length;
		} else {
			free(r);
		}
	}
	return err;
}


