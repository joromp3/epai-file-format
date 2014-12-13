/* See LICENSE file for copyright and license terms. */

/* decoder.h: header for matadata.c */

#ifndef LIBEPAI_METADATA_H
#define LIBEPAI_METADATA_H


#define EPAI_METADATA_MAX_PAIRS 256
#define EPAI_METADATA_KEY_LEN 16
#define EPAI_METADATA_VAL_LEN 256


typedef struct {
        epai_section_type_t type;
        uint32_t length;
	int num_pairs;
	int* keylens;
	int* vallens;
	char** keys;
	char** values;
} epai_metadata_section_t;


/* check if all characters in a string are valid for a metadata key */
extern int epai_metadata_validate_key_string(const char*, uint32_t);

/* free/destroy a metadata struct */
extern void epai_metadata_free_struct(epai_metadata_section_t*);

/* allocate a new metadata struct */
extern epai_error_t epai_metadata_new_struct(epai_metadata_section_t**);

/* add a new metadata pair to a struct */
extern epai_error_t epai_metadata_add_pair(epai_metadata_section_t*,
		const char*, const char*);

/* remove a metadata pair with index */
extern epai_error_t epai_metadata_remove_pair_by_index(epai_metadata_section_t*,
		int);

/* validate a blob of encoded metadata */
extern epai_error_t epai_metadata_validate_blob(const char*, uint32_t);

/* parse a blob of encoded metadata into a new struct */
extern epai_error_t epai_metadata_parse_blob(epai_metadata_section_t**,
		const char*, uint32_t);

/* encode a metadata section into an existing buffer */
extern epai_error_t epai_metadata_fill_blob(const epai_metadata_section_t*,
	char*, uint32_t);

/* encode a metadata section into a new buffer */
extern epai_error_t epai_metadata_new_blob(const epai_metadata_section_t*,
		char**, uint32_t*);

/* return the length of the encoded metadata section at pointer */
extern uint32_t epai_metadata_parse_length(const char*);

/* return the length needed to encode metadata */
extern uint32_t epai_metadata_encode_length(const epai_metadata_section_t*);


#endif /* LIBEPAI_METADATA_H */
