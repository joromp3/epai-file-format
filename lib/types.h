/* See LICENSE file for copyright and license terms. */

/* types.h: header for type definitions. */

#ifndef LIBEPAI_TYPES_H
#define LIBEPAI_TYPES_H

/* to be used for byte buffers; text strings should use regular char type */
typedef unsigned char epai_byte_t;

typedef enum {
	EPAI_ENDIAN_NATIVE,
	EPAI_ENDIAN_LITTLE,
	EPAI_ENDIAN_BIG
} epai_endian_t;

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


#endif /* LIBEPAI_TYPES_H */

