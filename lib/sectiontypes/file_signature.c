/* See LICENSE file for copyright and license terms. */

/*
 * file_signature.c: implementation of functions related to the file
 * signature section in the EPAI format.
 */


#include "../common.h"
#include "../epai.h"


/* According to spec, all file signatures must be of exactly this length. */
static const int file_signature_header_len = 11;


/* Refuse to accept file signature headers with format version > this. */
static int max_format_version = 0x00;


extern void epai_file_signature_free_struct(epai_fsign_section_t* ssp) {
	free(ssp);
}

extern epai_error_t epai_file_signature_new_struct(epai_fsign_section_t** ssp) {
	epai_fsign_section_t* ns = malloc(sizeof(**ssp));
	if (ns == NULL) {
		epai_set_error("Could not allocate memory for new file signature struct.");
		return EPAI_ERROR_MALLOC;
	}

	ns->type = EPAI_SECTION_FILE_SIGNATURE;

	*ssp = ns;

	return EPAI_SUCCESS;
}


extern epai_error_t epai_file_signature_validate_blob(const epai_byte_t* buffer,
						      uint32_t len) {
	unsigned int endian_marker;

	if (len != file_signature_header_len) {
		epai_set_error("Invalid blob length for file signature.");
		return EPAI_ERROR_SECTION_LENGTH;
	}

	if (*buffer != EPAI_SECTION_FILE_SIGNATURE) {
		epai_set_error("Could not validate section blob: "
				"section type code byte is not File Signature.");
		return EPAI_ERROR_SECTION_TYPE;
	}

	if (*++buffer != 'E' || *++buffer != 'P' ||
	    *++buffer != 'A' || *++buffer != 'I' ||
	    *++buffer != 0x0d || *++buffer != 0x0a || *++buffer != 0x0a) {
		epai_set_error("Invalid file signature header; blob likely corrupt.");
		return EPAI_ERROR_BAD_FILE_SIGNATURE;
	}

	if (*++buffer > max_format_version) {
		epai_set_error("Unsupported blob file format version.");
		return EPAI_ERROR_VERSION_UNSUPPORTED;
	}

	endian_marker = *++buffer;
	endian_marker |= *++buffer << 8;

	/* Validation should pass regardless of file endian. */
	if (!(endian_marker == 0xAF00 || endian_marker == 0x00AF)) {
		epai_set_error("Invalid endian marker in file signature blob.");
		return EPAI_ERROR_BAD_FILE_SIGNATURE;
	}

	return EPAI_SUCCESS;
}


extern epai_error_t epai_file_signature_parse_blob(epai_fsign_section_t** ssp,
		epai_file_t* file, const epai_byte_t* buffer, uint32_t len) {
	epai_error_t err = epai_file_signature_validate_blob(buffer, len);
	epai_fsign_section_t* ns;
	uint16_t em;

	if (err != EPAI_SUCCESS) {
		return err;
	}

	err = epai_file_signature_new_struct(&ns);

	if (err != EPAI_SUCCESS) {
		return err;
	}

	em = le16toh(*(buffer+9) << 8 | *(buffer+10));

	switch (em) {
	case 0xAF00:
		file->endian = EPAI_ENDIAN_BIG;
		break;
	case 0x00AF:
		file->endian = EPAI_ENDIAN_LITTLE;
		break;
	default:
		epai_set_error("Failed to parse file signature: bad endian marker.");
		return EPAI_ERROR_BAD_FILE_SIGNATURE;
	}

	*ssp = ns;

	return EPAI_SUCCESS;
}


extern uint32_t epai_file_signature_parse_length(const epai_file_t* file,
		const epai_byte_t* buffer) {
	return file_signature_header_len;
}

extern uint32_t epai_file_signature_encode_length(const epai_fsign_section_t* ssp) {
	return file_signature_header_len;
}


extern epai_error_t epai_file_signature_fill_blob(const epai_fsign_section_t* ssp,
		const epai_file_t* file, epai_byte_t* buffer, uint32_t len) {

	if (len < file_signature_header_len) {
		epai_set_error("Could not fill buffer with file signature blob: "
				"buffer too short.");
		return EPAI_ERROR_SECTION_LENGTH;
	}

	*buffer = EPAI_SECTION_FILE_SIGNATURE;
	*++buffer = 'E';
	*++buffer = 'P';
	*++buffer = 'A';
	*++buffer = 'I';
	*++buffer = 0x0D;
	*++buffer = 0x0A;
	*++buffer = 0x0A;
	*++buffer = file->version;

	switch (file->endian) {
	case EPAI_ENDIAN_NATIVE:
		*((uint16_t*)(++buffer)) = 0xAF00;
		break;
	case EPAI_ENDIAN_LITTLE:
		*++buffer = 0x00;
		*++buffer = 0xAF;
		break;
	case EPAI_ENDIAN_BIG:
		*++buffer = 0xAF;
		*++buffer = 0x00;
		break;
	}

	return EPAI_SUCCESS;
}

extern epai_error_t epai_file_signature_new_blob(const epai_fsign_section_t* ssp,
		const epai_file_t* file, epai_byte_t** out, uint32_t* len) {
	epai_byte_t* r = malloc(file_signature_header_len);
	epai_error_t err;

	if (r == NULL) {
		epai_set_error("Could not allocate memory for new file signature blob.");
		err = EPAI_ERROR_MALLOC;
	} else {
		err = epai_file_signature_fill_blob(ssp, file, r,
				file_signature_header_len);
		if (err == EPAI_SUCCESS) {
			*out = r;
			*len = file_signature_header_len;
		} else {
			free(r);
		}
	}

	return err;
}
