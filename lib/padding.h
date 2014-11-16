/* See LICENSE file for copyright and license terms. */

/* padding.h: header for padding.c */

#ifndef LIBEPAI_PADDING_H
#define LIBEPAI_PADDING_H


typedef struct {
	epai_section_type_t type;
	uint32_t length;
} epai_padding_section_t;


/** \fn epai_error_t epai_validate_padding_blob(const char* buffer, uint32_t len)
    \brief Validate a file padding section in memory.
    \param buffer Pointer to padding section.
    \param len Length of padding section, including section header.
    \return EPAI_SUCCESS if valid, or the error if not.
*/
extern epai_error_t epai_validate_padding_blob(const char*, uint32_t);


/** \fn epai_error_t epai_new_padding_blob(const epai_padding_section_t* ssp,
                                           char** out, uint32_t* len)
    \brief Allocate new memory and generate a new padding section binary in it.
    \param ssp Pointer to the section struct.
    \param out On success, will be set to a pointer to the new memory.
    \param len On success, will be set to the length of the new memory chunk.
    \return EPAI_SUCCESS on success, some error otherwise.
*/
extern epai_error_t epai_new_padding_blob(const epai_padding_section_t*,
					  char**, uint32_t*);


#endif /* LIBEPAI_PADDING_H */
