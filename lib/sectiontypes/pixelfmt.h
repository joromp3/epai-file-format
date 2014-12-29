/* See LICENSE file for copyright and license terms. */

/* image.h: definitions for EPAI image sections. */


#ifndef LIBEPAI_PIXELFMT_H
#define LIBEPAI_PIXELFMT_H


#define EPAI_PIXELFMT_MAX_CHANNELS 16


typedef enum {
	EPAI_CHANFMT_INT1  = 0,
	EPAI_CHANFMT_INT4  = 1,
	EPAI_CHANFMT_INT8  = 2,
	EPAI_CHANFMT_INT16 = 3,
	EPAI_CHANFMT_INT24 = 4,
	EPAI_CHANFMT_INT32 = 5,
	EPAI_CHANFMT_FLT16 = 8,
	EPAI_CHANFMT_FLT32 = 9,
	EPAI_CHANFMT_FLT64 = 10
} epai_chanfmt_t;

typedef enum {
	EPAI_CHANUSG_INDEX = 0,
	EPAI_CHANUSG_RED = 1,
	EPAI_CHANUSG_GREEN = 2,
	EPAI_CHANUSG_BLUE = 3,
	EPAI_CHANUSG_ALPHA = 4,
	EPAI_CHANUSG_DEPTH = 5,
	EPAI_CHANUSG_MASK = 6,
	EPAI_CHANUSG_SX = 8,
	EPAI_CHANUSG_SY = 9,
	EPAI_CHANUSG_SZ = 10,
	EPAI_CHANUSG_SHEIGHT = 11,
	EPAI_CHANUSG_SDIFFUSE = 12,
	EPAI_CHANUSG_SSPECULAR = 13
} epai_chanusg_t;

typedef struct {
	epai_chanfmt_t fmt;
	epai_chanusg_t usage;
} epai_channel_t;

typedef struct {
        epai_section_type_t type;
        int nchannels;
        epai_channel_t* channels;
} epai_pixelfmt_section_t;


/* free an existing pixelfmt struct */
extern void epai_pixelfmt_free_struct(epai_pixelfmt_section_t*);

/* allocate a new pixelfmt struct */
extern epai_error_t epai_pixelfmt_new_struct(epai_pixelfmt_section_t**);

/* validate a blob with encoded pixelfmt data */
extern epai_error_t epai_pixelfmt_validate_blob(const epai_byte_t*, uint32_t);

/* parse a pixelfmt blob into a new struct */
extern epai_error_t epai_pixelfmt_parse_blob(epai_pixelfmt_section_t**,
		const epai_byte_t*, uint32_t);

/* encode a pixelfmt section into an existing buffer */
extern epai_error_t epai_pixelfmt_fill_blob(const epai_pixelfmt_section_t*,
		epai_byte_t*, uint32_t);

/* encode a pixelfmt section into a new buffer */
extern epai_error_t epai_pixelfmt_new_blob(const epai_pixelfmt_section_t*,
					  epai_byte_t**, uint32_t*);

/* return the length of the encoded pixelfmt section at pointer */
extern uint32_t epai_pixelfmt_parse_length(const epai_byte_t*);

/* return the length needed to encode pixelfmt */
extern uint32_t epai_pixelfmt_encode_length(const epai_pixelfmt_section_t*);


#endif /* LIBEPAI_PIXELFMT_H */
