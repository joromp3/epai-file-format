/* See LICENSE file for copyright and license terms. */

/* generic_section.h: generic section types. */

#ifndef LIBEPAI_GENERIC_SECTION_H
#define LIBEPAI_GENERIC_SECTION_H


/* validate the common parts of optional sections in a blob of encoded data. */
extern epai_error_t epai_validate_optional_section_blob(const epai_byte_t*, uint32_t);

/* return the length of the encoded optional section at pointer */
extern uint32_t epai_optional_section_parse_length(const epai_file_t*, const epai_byte_t*);

/* return the length needed to encode optional section */
extern uint32_t epai_optional_section_encode_length(const epai_optional_section_t*);


/* generic dispatch functions */

extern epai_error_t epai_section_free_struct(epai_section_t*);
extern epai_error_t epai_section_new_struct(epai_section_t**, epai_section_type_t);
extern epai_error_t epai_section_validate_blob(const epai_byte_t*, uint32_t);
extern epai_error_t epai_section_parse_blob(epai_section_t**, epai_file_t*, const epai_byte_t*, uint32_t);
extern epai_error_t epai_section_fill_blob(const epai_section_t*, const epai_file_t*, epai_byte_t*, uint32_t);
extern epai_error_t epai_section_new_blob(const epai_section_t*, const epai_file_t*, epai_byte_t**, uint32_t*);
extern uint32_t epai_section_parse_length(const epai_file_t*, const epai_byte_t*);
extern uint32_t epai_section_encode_length(const epai_section_t*);


#endif /* LIBEPAI_GENERIC_SECTION_H */
