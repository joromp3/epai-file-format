/* See LICENSE file for copyright and license terms. */

/* encoder.c: encoding entire EPAI files. */


#include "common.h"
#include "epai.h"


extern void epai_encoder_free(epai_encoder_t* es, int free_file) {
	if (free_file) {
		epai_file_free(es->file);
	}
	free(es);
}

extern epai_error_t epai_encoder_new_with_file(epai_encoder_t** es, epai_file_t* f) {
	epai_encoder_t* ns = malloc(sizeof(*ns));

	if (ns == NULL) {
		return EPAI_ERROR_MALLOC;
	}

	ns->file = f;

	*es = ns;

	return EPAI_SUCCESS;
}

extern epai_error_t epai_encoder_new(epai_encoder_t** es) {
	epai_file_t* nf;
	epai_error_t err;

	err = epai_file_new(&nf, EPAI_ENDIAN_LITTLE);
	if (err) {
		return err;
	}

	err = epai_encoder_new_with_file(es, nf);
	if (err) {
		epai_file_free(nf);
		return err;
	}

	return EPAI_SUCCESS;
}

extern epai_error_t epai_encoder_encode_to_ptr(const epai_decoder_t* es, char** pout) {
	size_t total_len = 0;
	char* aout, cp;
	epai_error_t err;
	int i;

	for (i = 0; i < es->file->num_sections; ++i) {
		total_len += epai_section_encode_length(es->file->sections[i]);
	}

	aout = malloc(total_len);
	if (aout == NULL) {
		return EPAI_ERROR_MALLOC;
	}

	cp = aout;

	for (i = 0; i < es->file->num_sections; ++i) {
		uint32_t slen = epai_section_encode_length(es->file->sections[i]);

		err = epai_section_fill_blob(es->file->sections[i], cp, slen);
		if (err) {
			free(aout);
			return err;
		}

		cp += slen;
	}

	*pout = aout;

	return EPAI_SUCCESS;
}
