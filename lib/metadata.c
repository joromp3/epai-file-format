/* See LICENSE file for copyright and license terms. */

/*
 * metadata.c: implementation of functions related to the text metadata
 * section in the EPAI format.
 */


#include "common.h"
#include "epai.h"


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
		return EPAI_ERROR_MALLOC;
	}

	ns->type = EPAI_SECTION_METADATA;
	ns->num_pairs = 0;

	ns->keylens = calloc(EPAI_METADATA_MAX_PAIRS, sizeof(int));
	ns->vallens = calloc(EPAI_METADATA_MAX_PAIRS, sizeof(int));
	ns->keys = calloc(EPAI_METADATA_MAX_PAIRS, sizeof(char*));
	ns->values = calloc(EPAI_METADATA_MAX_PAIRS, sizeof(char*));

	if (ns->keylens == NULL ||
	    ns->vallens == NULL ||
	    ns->keys == NULL ||
	    ns->values == NULL) {
		epai_metadata_free_struct(ns);
		return EPAI_ERROR_MALLOC;
	}

	for (i = 0; i < EPAI_METADATA_MAX_PAIRS; ++i) {
		ns->keys[i] = malloc(EPAI_METADATA_KEY_LEN);
		ns->values[i] = malloc(EPAI_METADATA_VAL_LEN);

		if (ns->keys[i] == NULL || ns->values[i] == NULL) {
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

	if (keylen > EPAI_METADATA_KEY_LEN ||
	    vallen > EPAI_METADATA_VAL_LEN ||
	    ssp->num_pairs >= EPAI_METADATA_MAX_PAIRS) {
		return EPAI_ERROR_METADATA_LIMITS;
	}

	strncpy(ssp->keys[ssp->num_pairs], key, EPAI_METADATA_KEY_LEN);
	strncpy(ssp->values[ssp->num_pairs], value, EPAI_METADATA_VAL_LEN);
	ssp->keylens[ssp->num_pairs] = keylen;
	ssp->vallens[ssp->num_pairs] = vallen;
	++ssp->num_pairs;

	return EPAI_SUCCESS;
}

extern epai_error_t epai_metadata_remove_pair_by_index(epai_metadata_section_t* ssp,
		int index) {
	char *tempk, *tempv;
	int i;

	if (index >= ssp->num_pairs ||
	    index < 0) {
		return EPAI_ERROR_METADATA_LIMITS;
	}

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


extern epai_error_t epai_metadata_validate_blob(const char* buffer,
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

		if (!epai_metadata_validate_key_string(buffer, keylen)) {
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


extern epai_error_t epai_metadata_parse_blob(epai_metadata_section_t** ssp,
		const char* buffer, uint32_t len) {
	epai_error_t error = epai_metadata_validate_blob(buffer, len);
	int kl, vl;

	if (error) {
		return error;
	}

	error = epai_metadata_new_struct(ssp);

	buffer += 5;
	len -= 5;
	while (len > 0) {
		const char* vp;
		kl = strlen(buffer);
		vp = buffer + kl;
		vl = strlen(buffer);

		error = epai_metadata_add_pair(*ssp, buffer, vp);
		if (error) {
			epai_metadata_free_struct(*ssp);
			return error;
		}

		buffer = vp + vl;
		len -= kl + vl;
	}

	return EPAI_SUCCESS;
}


static uint32_t epai_metadata_calculate_blob_length(const epai_metadata_section_t* ssp) {
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


extern epai_error_t epai_metadata_fill_blob(const epai_metadata_section_t* ssp,
	char* out, uint32_t len) {
	int i;
	uint32_t l = epai_metadata_calculate_blob_length(ssp);

	if (l > len) {
		return EPAI_ERROR_SECTION_LENGTH;
	}

	*out = EPAI_SECTION_METADATA;
	/* FIXME handle endian */
	*(uint32_t*)(out + 1) = l - 5;
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
					   char** out, uint32_t* len) {
	epai_error_t err;
	uint32_t l;
	char *r;

	l = epai_metadata_calculate_blob_length(ssp);

	r = malloc(l);
	if (r == NULL) {
		return EPAI_ERROR_MALLOC;
	}

	err = epai_metadata_fill_blob(ssp, r, l);
	if (err) {
		return err;
	}

	*out = r;
	*len = l;

	return EPAI_SUCCESS;
}


