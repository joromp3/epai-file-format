/* See LICENSE file for copyright and license terms. */

/* decoder.c: decoding entire EPAI files. */


#include "common.h"
#include "epai.h"


extern void epai_decoder_free(epai_decoder_t* ds) {
	epai_file_free(ds->file);
	free(ds);
}

extern epai_error_t epai_decoder_new_from_ptr(epai_decoder_t** ds,
		const epai_byte_t* pin, size_t len) {
	epai_decoder_t* ns = malloc(sizeof(*ns));
	epai_error_t err;

	if (ns == NULL) {
		return EPAI_ERROR_MALLOC;
	}

	err = epai_file_new(&ns->file, EPAI_ENDIAN_LITTLE);
	if (err != EPAI_SUCCESS) {
		free(ns);
		return err;
	}

	ns->ptr_in = pin;
	ns->buf_len = len;

	*ds = ns;

	return EPAI_SUCCESS;
}

extern epai_error_t epai_decoder_decode(epai_decoder_t* ds) {
	epai_error_t err;
	uint32_t sec_len, total_len = ds->buf_len;
	const epai_byte_t *sp = ds->ptr_in;
	epai_section_t* sec;

	sec_len = epai_file_signature_parse_length(sp);
	if (sec_len > total_len) {
		return EPAI_ERROR_SECTION_LENGTH;
	}

	epai_file_signature_free_struct(ds->file->sections[0]);
	err = epai_file_signature_parse_blob(&ds->file->sections[0],
			sp, sec_len);

	if (err != EPAI_SUCCESS) {
		return err;
	}

	sp += sec_len;
	total_len -= sec_len;

	while (total_len > 0) {
		sec_len = epai_section_parse_length(sp);
		if (sec_len > total_len) {
			return EPAI_ERROR_SECTION_LENGTH;
		}

		err = epai_section_parse_blob(&sec, sp, sec_len);
		if (err != EPAI_SUCCESS) {
			return err;
		}

		err = epai_file_add_section(ds->file, sec);
		if (err != EPAI_SUCCESS) {
			return err;
		}

		sp += sec_len;
		total_len -= sec_len;
	}

	err = epai_file_validate_struct(ds->file);

	return EPAI_SUCCESS;
}
