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

extern epai_error_t epai_encoder_new(epai_encoder_t** es, epai_file_t* f) {
	epai_file_t* nf = f;
	epai_encoder_t* ns;
	epai_error_t err;

	if (f == NULL) {
		err = epai_file_new(&nf, EPAI_ENDIAN_NATIVE);
		if (err != EPAI_SUCCESS) {
			return err;
		}
	}

	ns = malloc(sizeof(*ns));
	if (ns == NULL) {
		if (f == NULL) {
			epai_file_free(nf);
		}
		epai_set_error("Could not allocate memory for new encoder struct.");
		return EPAI_ERROR_MALLOC;
	}

	ns->file = nf;

	*es = ns;

	return EPAI_SUCCESS;
}

extern epai_error_t epai_encoder_encode_to_ptr(const epai_decoder_t* es,
		epai_byte_t** pout) {
	size_t total_len = 0;
	epai_byte_t *aout, *cp;
	epai_error_t err;
	int i;

	for (i = 0; i < es->file->num_sections; ++i) {
		total_len += epai_section_encode_length(es->file->sections[i]);
	}

	aout = malloc(total_len);
	if (aout == NULL) {
		epai_set_error("Encoding failed: could not allocate memory "
				"for output buffer.");
		return EPAI_ERROR_MALLOC;
	}

	cp = aout;

	for (i = 0; i < es->file->num_sections; ++i) {
		uint32_t slen = epai_section_encode_length(es->file->sections[i]);

		err = epai_section_fill_blob(es->file->sections[i], es->file, cp, slen);
		if (err != EPAI_SUCCESS) {
			free(aout);
			return err;
		}

		cp += slen;
	}

	*pout = aout;

	return EPAI_SUCCESS;
}