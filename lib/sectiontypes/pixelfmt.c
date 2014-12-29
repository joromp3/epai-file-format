/* See LICENSE file for copyright and license terms. */

/*
 * pixelfmt.c: implementation of the EPAI pixel format section type.
 */


#include "../common.h"
#include "../epai.h"


extern void epai_pixelfmt_free_struct(epai_pixelfmt_section_t* ssp) {
	free(ssp->channels);
	free(ssp);
}


extern epai_error_t epai_pixelfmt_new_struct(epai_pixelfmt_section_t** ssp) {
	epai_pixelfmt_section_t* ns;

	ns = malloc(sizeof(*ns));
	if (ns == NULL) {
		epai_set_error("Could not allocate memory for new pixelfmt struct.");
		return EPAI_ERROR_MALLOC;
	}

	ns->channels = malloc(sizeof(*(ns->channels)) * EPAI_PIXELFMT_MAX_CHANNELS);
	if (ns->channels == NULL) {
		epai_set_error("Could not allocate memory for new pixelfmt channels.");
		return EPAI_ERROR_MALLOC;
	}

	ns->type = EPAI_SECTION_PIXELFMT;
	ns->nchannels = 0;

	*ssp = ns;

	return EPAI_SUCCESS;
}

extern epai_error_t epai_pixelfmt_validate_blob(const epai_byte_t* buffer, uint32_t len) {
	int nchannels;

	if (*buffer != EPAI_SECTION_PIXELFMT) {
		epai_set_error("Could not validate section blob: "
				"section type code byte is not Pixel Format.");
		return EPAI_ERROR_SECTION_TYPE;
	}

	nchannels = *(buffer + 1);

	if (len != nchannels + 2) {
		epai_set_error("Invalid pixel format blob: buffer length mismatch.");
		return EPAI_ERROR_SECTION_LENGTH;
	}

	return EPAI_SUCCESS;
}

extern epai_error_t epai_pixelfmt_parse_blob(epai_pixelfmt_section_t** ssp,
		epai_file_t* file, const epai_byte_t* buffer, uint32_t len) {
	epai_error_t err = epai_pixelfmt_validate_blob(buffer, len);
	epai_pixelfmt_section_t* ns;
	int i;

	if (err != EPAI_SUCCESS) {
		return err;
	}

	err = epai_pixelfmt_new_struct(&ns);
	if (err != EPAI_SUCCESS) {
		return err;
	}

	ns->nchannels = *(buffer + 1);

	for (i = 0; i < ns->nchannels; ++i) {
		ns->channels[i].usage = *(buffer + 2 + i) & 0xF;
		ns->channels[i].fmt = *(buffer + 2 + i) >> 4;
	}

	*ssp = ns;

	return EPAI_SUCCESS;
}

extern uint32_t epai_pixelfmt_parse_length(const epai_file_t* file,
		const epai_byte_t* buffer) {
	return *(buffer + 1) + 2;
}

extern uint32_t epai_pixelfmt_encode_length(const epai_pixelfmt_section_t* ssp) {
	return ssp->nchannels + 2;
}

extern epai_error_t epai_pixelfmt_fill_blob(const epai_pixelfmt_section_t* ssp,
		const epai_file_t* file, epai_byte_t* buffer, uint32_t len) {
	int i;

	if (ssp->nchannels == 0) {
		epai_set_error("Pixel format must have at least one channel.");
		return EPAI_ERROR_SECTION_LENGTH;
	}

	if (len < ssp->nchannels + 2) {
		epai_set_error("Cannot fill buffer with pixel format blob: "
				"buffer too short.");
		return EPAI_ERROR_SECTION_LENGTH;
	}

	*buffer = EPAI_SECTION_PIXELFMT;
	*(buffer + 1) = ssp->nchannels;

	for (i = 0; i < ssp->nchannels; ++i) {
		*(buffer + 2 + i) = ssp->channels[i].fmt << 4 |
				(ssp->channels[i].usage & 0xF);
	}

	return EPAI_SUCCESS;
}

extern epai_error_t epai_pixelfmt_new_blob(const epai_pixelfmt_section_t* ssp,
		  const epai_file_t* file, epai_byte_t** out, uint32_t* len) {
	epai_byte_t* r = malloc(ssp->nchannels + 2);
	epai_error_t err;

	if (r == NULL) {
		epai_set_error("Could not allocate memory for new pixelfmt blob.");
		err = EPAI_ERROR_MALLOC;
	} else {
		err = epai_pixelfmt_fill_blob(ssp, file, r, ssp->nchannels + 2);
		if (err == EPAI_SUCCESS) {
			*out = r;
			*len = ssp->nchannels + 2;
		} else {
			free(r);
		}
	}

	return err;
}
