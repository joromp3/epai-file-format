/* See LICENSE file for copyright and license terms. */

/*
 * checksum.c: implementation of functions related to chechsum

 * section in the EPAI format.
 */


#include "common.h"
#include "epai.h"



uint32_t epai_crc32(uint32_t crc, const epai_byte_t *buf, size_t len){
	static uint32_t table[256];
	static int have_table = 0;// first call is slower
	uint32_t rem;
	uint8_t octet;
	int i, j;
	const epai_byte_t *p, *q;

	// This check is not thread safe; there is no mutex.
	if (have_table == 0) {
		// Calculate CRC table.
		for (i = 0; i < 256; i++) {
			rem = i;  // remainder from polynomial division
			for (j = 0; j < 8; j++) {
				if (rem & 1) {
					rem >>= 1;
					rem ^= 0xedb88320;
				} else
					rem >>= 1;
			}
			table[i] = rem;
		}
		have_table = 1;
	}

	crc = ~crc;
	q = buf + len;
	for (p = buf; p < q; p++) {
		octet = *p;  // Cast to unsigned octet.
		crc = (crc >> 8) ^ table[(crc & 0xff) ^ octet];
	}
	return ~crc;
}

extern void epai_checksum_free_struct(epai_checksum_section_t* ssp) {
	free(ssp);
}

extern epai_error_t epai_checksum_new_struct(epai_checksum_section_t** ssp) {
	*ssp = malloc(sizeof(**ssp));
	if (*ssp == NULL) {
		return EPAI_ERROR_MALLOC;
	}

	(*ssp)->type = EPAI_SECTION_CHECKSUM;
	(*ssp)->length = 9;
	(*ssp)->checksum = 0;

	return EPAI_SUCCESS;
}


extern epai_error_t epai_checksum_validate_blob(const epai_byte_t* buffer, uint32_t len) {
	epai_error_t err = epai_validate_optional_section_blob(buffer, len);

	if (err != EPAI_SUCCESS) {
		return err;
	}

	if (*buffer != EPAI_SECTION_CHECKSUM) {
		return EPAI_ERROR_SECTION_TYPE;
	}

	return EPAI_SUCCESS;
}


extern epai_error_t epai_checksum_parse_blob(epai_checksum_section_t** ssp,
		const epai_byte_t* buffer, uint32_t len) {
	epai_error_t err = epai_checksum_validate_blob(buffer, len);

	if (err != EPAI_SUCCESS) {
		return err;
	}

	err = epai_checksum_new_struct(ssp);
	(*ssp)->length = len;

	if (err != EPAI_SUCCESS) {
		return err;
	}

	return EPAI_SUCCESS;
}


extern uint32_t epai_checksum_parse_length(const epai_byte_t* buffer) {
	/* FIXME endian */
	return *(uint32_t*)(buffer + 1);
}

extern uint32_t epai_checksum_encode_length(const epai_checksum_section_t* ssp) {
	return ssp->length;
}


extern epai_error_t epai_checksum_fill_blob(const epai_checksum_section_t* ssp,
		epai_byte_t* buffer, uint32_t len) {
	int i;

	if (ssp->length < 9 || len != ssp->length) {
		return EPAI_ERROR_SECTION_LENGTH;
	}

	*buffer = EPAI_SECTION_CHECKSUM;

	/* FIXME handle endian */
	*(uint32_t*) (buffer + 1) = ssp->length - 9;

	uint32_t res=epai_crc32(0,buffer+9,len-9);
	*(uint32_t*) (buffer + 5) = res;

	return EPAI_SUCCESS;
}

extern epai_error_t epai_checksum_new_blob(const epai_checksum_section_t* ssp,
		epai_byte_t** out, uint32_t* len) {
	epai_byte_t* r = malloc(ssp->length);
	epai_error_t err;

	if (r == NULL) {
		err = EPAI_ERROR_MALLOC;
	} else {
		err = epai_checksum_fill_blob(ssp, r, ssp->length);
		if (err == EPAI_SUCCESS) {
			*out = r;
			*len = ssp->length;
		} else {
			free(r);
		}
	}

	return err;
}
