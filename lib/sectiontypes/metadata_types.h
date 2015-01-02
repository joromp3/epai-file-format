/* See LICENSE file for copyright and license terms. */

/* metadata_types.h: metadata type definitions. */

#ifndef LIBEPAI_METADATA_TYPES_H
#define LIBEPAI_METADATA_TYPES_H

typedef struct {
        epai_section_type_t type;
        uint32_t length;
	int num_pairs;
	int* keylens;
	int* vallens;
	char** keys;
	char** values;
} epai_metadata_section_t;

#endif /* LIBEPAI_METADATA_TYPES_H */

