/* See LICENSE file for copyright and license terms. */

/* types.h: header for type definitions. */

#ifndef LIBEPAI_TYPES_H
#define LIBEPAI_TYPES_H

typedef enum {
	/* No error. */
	EPAI_SUCCESS,
	/* Undefined error (!EPAI_SUCCESS). */
	EPAI_ERROR_UNSPECIFIED,
	/* Bad section type code. */
	EPAI_ERROR_SECTION_TYPE,
	/* Corrupt file signature. */
	EPAI_ERROR_BAD_FILE_SIGNATURE,
	/* Unsupported format version. */
	EPAI_ERROR_VERSION_UNSUPPORTED
} epai_error_t;

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
	EPAI_SECTION_PIXEL_FORMAT = 0x81,
	EPAI_SECTION_PALETTE = 0x82,
	EPAI_SECTION_IMAGE = 0x83,
	EPAI_SECTION_KEYFRAME = 0x84
} epai_section_type_t;


#endif /* LIBEPAI_TYPES_H */
