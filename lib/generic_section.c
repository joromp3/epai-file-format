/* See LICENSE file for copyright and license terms. */

/*
 * generic_section.c: functions that operate on different kinds of sections.
 */


#include "common.h"
#include "epai.h"


extern epai_error_t epai_validate_optional_section_blob(const epai_byte_t* buffer,
							uint32_t len) {
	uint32_t inner_len;

	if (len < 5) {
		epai_set_error("Could not validate section blob: "
				"all optional sections must be at least 5 bytes long.");
		return EPAI_ERROR_SECTION_LENGTH;
	}

	if (*buffer & 0x80) {
		epai_set_error("Could not validate section blob: "
				"section type code byte not within optional range.");
		return EPAI_ERROR_SECTION_TYPE;
	}

	/* maybe add length check */

	return EPAI_SUCCESS;
}


extern uint32_t epai_optional_section_parse_length(const epai_file_t* file,
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

extern uint32_t epai_optional_section_encode_length(const epai_optional_section_t* ssp) {
	return ssp->length;
}


extern epai_error_t epai_section_free_struct(epai_section_t* ssp) {
	switch (ssp->type) {
	case EPAI_SECTION_FILE_SIGNATURE:
		epai_file_signature_free_struct(ssp);
		break;
	case EPAI_SECTION_PADDING:
		epai_padding_free_struct(ssp);
		break;
	case EPAI_SECTION_METADATA:
		epai_metadata_free_struct(ssp);
		break;
	case EPAI_SECTION_PIXELFMT:
		epai_pixelfmt_free_struct(ssp);
		break;
	default:
		epai_set_error("Failed to dispatch section free:"
				"unknown section type.");
		return EPAI_ERROR_SECTION_TYPE;
	}

	return EPAI_SUCCESS;
}

extern epai_error_t epai_section_new_struct(epai_section_t** ssp,
		epai_section_type_t type) {
	switch (type) {
	case EPAI_SECTION_FILE_SIGNATURE:
		return epai_file_signature_new_struct(ssp);
	case EPAI_SECTION_PADDING:
		return epai_padding_new_struct(ssp);
	case EPAI_SECTION_METADATA:
		return epai_metadata_new_struct(ssp);
	case EPAI_SECTION_PIXELFMT:
		return epai_pixelfmt_new_struct(ssp);
	default:
		epai_set_error("Failed to dispatch section allocation:"
				"unknown section type.");
		return EPAI_ERROR_SECTION_TYPE;
	}
}

extern epai_error_t epai_section_validate_blob(const epai_byte_t* buffer, uint32_t len) {
	switch (*buffer) {
	case EPAI_SECTION_FILE_SIGNATURE:
		return epai_file_signature_validate_blob(buffer, len);
	case EPAI_SECTION_PADDING:
		return epai_padding_validate_blob(buffer, len);
	case EPAI_SECTION_METADATA:
		return epai_metadata_validate_blob(buffer, len);
	case EPAI_SECTION_PIXELFMT:
		return epai_pixelfmt_validate_blob(buffer, len);
	default:
		if (*buffer & 0x80) {
			epai_set_error("Failed to dispatch section blob validation:"
					"unknown section type.");
			return EPAI_ERROR_SECTION_TYPE;
		} else {
			return epai_validate_optional_section_blob(buffer, len);
		}
	}
}

extern epai_error_t epai_section_parse_blob(epai_section_t** ssp,
		epai_file_t* file, const epai_byte_t* buffer, uint32_t len) {
	switch (*buffer) {
	case EPAI_SECTION_FILE_SIGNATURE:
		return epai_file_signature_parse_blob(ssp, file, buffer, len);
	case EPAI_SECTION_PADDING:
		return epai_padding_parse_blob(ssp, file, buffer, len);
	case EPAI_SECTION_METADATA:
		return epai_metadata_parse_blob(ssp, file, buffer, len);
	case EPAI_SECTION_PIXELFMT:
		return epai_pixelfmt_parse_blob(ssp, file, buffer, len);
	default:
		epai_set_error("Failed to dispatch section parse:"
				"unknown section type.");
		return EPAI_ERROR_SECTION_TYPE;
	}
}

extern epai_error_t epai_section_fill_blob(const epai_section_t* ssp,
		const epai_file_t* file, epai_byte_t* buffer, uint32_t len) {
	switch (ssp->type) {
	case EPAI_SECTION_FILE_SIGNATURE:
		return epai_file_signature_fill_blob(ssp, file, buffer, len);
	case EPAI_SECTION_PADDING:
		return epai_padding_fill_blob(ssp, file, buffer, len);
	case EPAI_SECTION_METADATA:
		return epai_metadata_fill_blob(ssp, file, buffer, len);
	case EPAI_SECTION_PIXELFMT:
		return epai_pixelfmt_fill_blob(ssp, file, buffer, len);
	default:
		epai_set_error("Failed to dispatch section blob fill:"
				"unknown section type.");
		return EPAI_ERROR_SECTION_TYPE;
	}
}

extern epai_error_t epai_section_new_blob(const epai_section_t* ssp,
		const epai_file_t* file, epai_byte_t** buffer, uint32_t* len) {
	switch (ssp->type) {
	case EPAI_SECTION_FILE_SIGNATURE:
		return epai_file_signature_new_blob(ssp, file, buffer, len);
	case EPAI_SECTION_PADDING:
		return epai_padding_new_blob(ssp, file, buffer, len);
	case EPAI_SECTION_METADATA:
		return epai_metadata_new_blob(ssp, file, buffer, len);
	case EPAI_SECTION_PIXELFMT:
		return epai_pixelfmt_new_blob(ssp, file, buffer, len);
	default:
		epai_set_error("Failed to dispatch section blob allocation:"
				"unknown section type.");
		return EPAI_ERROR_SECTION_TYPE;
	}
}

extern uint32_t epai_section_parse_length(const epai_file_t* file,
		const epai_byte_t* buffer) {
	switch (*buffer) {
	case EPAI_SECTION_FILE_SIGNATURE:
		return epai_file_signature_parse_length(file, buffer);
	case EPAI_SECTION_PADDING:
		return epai_padding_parse_length(file, buffer);
	case EPAI_SECTION_METADATA:
		return epai_metadata_parse_length(file, buffer);
	case EPAI_SECTION_PIXELFMT:
		return epai_pixelfmt_parse_length(file, buffer);
	default:
		if (*buffer & 0x80) {
			return 0;
		} else {
			return epai_optional_section_parse_length(file, buffer);
		}
	}
}

extern uint32_t epai_section_encode_length(const epai_section_t* ssp) {
	switch (ssp->type) {
	case EPAI_SECTION_FILE_SIGNATURE:
		return epai_file_signature_encode_length(ssp);
	case EPAI_SECTION_PADDING:
		return epai_padding_encode_length(ssp);
	case EPAI_SECTION_METADATA:
		return epai_metadata_encode_length(ssp);
	case EPAI_SECTION_PIXELFMT:
		return epai_pixelfmt_encode_length(ssp);
	default:
		if (ssp->type & 0x80) {
			return 0;
		} else {
			return epai_optional_section_encode_length(ssp);
		}
	}
}
