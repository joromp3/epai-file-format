/* See LICENSE file for copyright and license terms. */

/* pixelfmt_types.h: pixelfmt type definitions. */

#ifndef LIBEPAI_PIXELFMT_TYPES_H
#define LIBEPAI_PIXELFMT_TYPES_H

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

#endif /* LIBEPAI_PIXELFMT_TYPES_H */

