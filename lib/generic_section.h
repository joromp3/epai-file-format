/* See LICENSE file for copyright and license terms. */

/* generic_section.h: header for generic_section.c */

#ifndef LIBEPAI_GENERIC_SECTION_H
#define LIBEPAI_GENERIC_SECTION_H


typedef union {
	epai_section_type_t type;
	epai_fsign_section_t fsign;
	epai_padding_section_t padding;
	epai_metadata_section_t metadata;
} epai_section_t;


/* validate the common parts of optional sections in a blob of encoded data. */
extern epai_error_t epai_validate_optional_section_blob(const char*, uint32_t);


#endif /* LIBEPAI_GENERIC_SECTION_H */
