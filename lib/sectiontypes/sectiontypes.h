/* See LICENSE file for copyright and license terms. */

/* sectiontypes.h: section type definitions. */

#ifndef LIBEPAI_SECTIONTYPES_H
#define LIBEPAI_SECTIONTYPES_H


typedef enum {
	/* Standard optional sections. */
	EPAI_SECTION_PADDING = 0x00,
	EPAI_SECTION_CHECKSUM = 0x01,
	EPAI_SECTION_METADATA = 0x02,
	EPAI_SECTION_COMPRESSED_TEXT = 0x03,
	EPAI_SECTION_FRAME = 0x04,
	EPAI_SECTION_GAMMA = 0x05,
	EPAI_SECTION_SPRITESHEET = 0x06,
	/* Standard mandatory sections. */
	EPAI_SECTION_FILE_SIGNATURE = 0x80,
	EPAI_SECTION_PIXELFMT = 0x81,
	EPAI_SECTION_PALETTE = 0x82,
	EPAI_SECTION_IMAGE = 0x83,
	EPAI_SECTION_KEYFRAME = 0x84
} epai_section_type_t;


#include "file_signature_types.h"
#include "metadata_types.h"
#include "padding_types.h"
#include "pixelfmt_types.h"


typedef struct {
	epai_section_type_t type;
	/* Full length with header; field in encoded file is this - 5. */
	uint32_t length;
} epai_optional_section_t;

typedef union {
	epai_section_type_t type;
	epai_fsign_section_t fsign;
	epai_optional_section_t opt;
	epai_padding_section_t padding;
	epai_metadata_section_t metadata;
	epai_pixelfmt_section_t pixelfmt;
} epai_section_t;


#endif /* LIBEPAI_SECTIONTYPES_H */
