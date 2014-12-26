/* See LICENSE file for copyright and license terms. */

/* padding.h: header for padding.c */

#ifndef LIBEPAI_PADDING_H
#define LIBEPAI_PADDING_H


typedef struct {
	epai_section_type_t type;
	uint32_t length;
} epai_padding_section_t;


/* free an existing padding struct */
extern void epai_padding_free_struct(epai_padding_section_t*);

/* allocate a new padding struct */
extern epai_error_t epai_padding_new_struct(epai_padding_section_t**);

/* validate a blob with encoded padding data */
extern epai_error_t epai_padding_validate_blob(const epai_byte_t*, uint32_t);

/* parse a padding blob into a new struct */
extern epai_error_t epai_padding_parse_blob(epai_padding_section_t**,
		const epai_byte_t*, uint32_t);

/* encode a padding section into an existing buffer */
extern epai_error_t epai_padding_fill_blob(const epai_padding_section_t*,
		epai_byte_t*, uint32_t);

/* encode a padding section into a new buffer */
extern epai_error_t epai_padding_new_blob(const epai_padding_section_t*,
					  epai_byte_t**, uint32_t*);

/* return the length of the encoded padding section at pointer */
extern uint32_t epai_padding_parse_length(const epai_byte_t*);

/* return the length needed to encode padding */
extern uint32_t epai_padding_encode_length(const epai_padding_section_t*);


#endif /* LIBEPAI_PADDING_H */
