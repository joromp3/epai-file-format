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

/** \fn epai_error_t epai_fill_padding_blob(char* buffer, epai_padding_section_t* ssp)
    \brief Generate a padding section binary in existing memory.
    \param buffer Pointer to location to fill with padding.
    \param ssp Pointer to the section struct.
    \return EPAI_SUCCESS on success; EPAI_ERROR_SECTION_LENGTH if length invalid.
*/
extern epai_error_t epai_fill_padding_blob(char*, epai_padding_section_t*);

/** \fn char* epai_new_padding_blob(epai_padding_section_t* ssp)
    \brief Allocate new memory and generate a new padding section binary in it.
    \param ssp Pointer to the section struct.
    \return Pointer to the new padding section, or NULL on failure.
*/
extern char* epai_new_padding_blob(epai_padding_section_t*);


#endif /* LIBEPAI_PADDING_H */
