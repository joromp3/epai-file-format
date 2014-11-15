/* See LICENSE file for copyright and license terms. */

/*
 * generic_section.c: functions that operate on different kinds of sections.
 */


#include "common.h"
#include "epai.h"


extern epai_error_t epai_validate_optional_section_blob(const char* buffer,
							uint32_t len) {
	uint32_t inner_len;

	if (len < 5) {
		return EPAI_ERROR_SECTION_LENGTH;
	}

	if (*buffer & 0x80) {
		return EPAI_ERROR_SECTION_TYPE;
	}

	/* FIXME: handle endian properly. */
	inner_len = *(uint32_t*)(buffer + 1);

	if (len != inner_len + 5) {
		return EPAI_ERROR_SECTION_LENGTH;
	}

	return EPAI_SUCCESS;
}

