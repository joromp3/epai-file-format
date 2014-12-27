/* See LICENSE file for copyright and license terms. */

/* file_signature.h: header for file_signature.c */

#ifndef LIBEPAI_FILE_SIGNATURE_H
#define LIBEPAI_FILE_SIGNATURE_H


typedef struct {
	epai_section_type_t type;
} epai_fsign_section_t;


/* free an existing file signature structure */
extern void epai_file_signature_free_struct(epai_fsign_section_t*);

/* allocate a new file signature structure */
extern epai_error_t epai_file_signature_new_struct(epai_fsign_section_t**);

/* validate a binary blob of encoded file signature data */
extern epai_error_t epai_file_signature_validate_blob(const epai_byte_t*, uint32_t);

/* parse a binary blob of encoded file signature data into a new struct */
extern epai_error_t epai_file_signature_parse_blob(epai_fsign_section_t**,
		const epai_byte_t*, uint32_t);

/* encode a file signature into an existing buffer */
extern epai_error_t epai_file_signature_fill_blob(const epai_fsign_section_t*,
		epai_byte_t*, uint32_t);

/* allocate a new buffer and encode a file signature into it */
extern epai_error_t epai_file_signature_new_blob(const epai_fsign_section_t*,
		epai_byte_t**, uint32_t*);

/* return the length of the encoded file signature section at pointer */
extern uint32_t epai_file_signature_parse_length(const epai_byte_t*);

/* return the length needed to encode file signature */
extern uint32_t epai_file_signature_encode_length(const epai_fsign_section_t*);


#endif /* LIBEPAI_FILE_SIGNATURE_H */

