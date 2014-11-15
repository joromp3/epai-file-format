/* See LICENSE file for copyright and license terms. */

/* padding.h: header for padding.c */

#ifndef LIBEPAI_PADDING_H
#define LIBEPAI_PADDING_H


/** \fn epai_error_t epai_validate_padding(const char* buffer, uint32_t len)
    \brief Validate a file padding section in memory.
    \param buffer Pointer to padding section.
    \param len Length of padding section, including section header.
    \return EPAI_SUCCESS if valid, or the error if not.
*/
extern epai_error_t epai_validate_padding(const char*, uint32_t);

/** \fn epai_error_t epai_fill_padding(char* buffer, uint32_t len)
    \brief Generate a padding section in existing memory.
    \param buffer Pointer to location to fill with padding.
    \param len Length of padding section. Must be >=5.
    \return EPAI_SUCCESS on success; EPAI_ERROR_SECTION_LENGTH if len invalid.
*/
extern epai_error_t epai_fill_padding(char*, uint32_t);

/** \fn char* epai_new_padding(uint32_t len)
    \brief Allocate new memory and generate a new padding section in it.
    \param len The length of the new padding memory chunk. Must be >=5.
    \return Pointer to the new padding section, or NULL on failure.
*/
extern char* epai_new_padding(uint32_t);


#endif /* LIBEPAI_PADDING_H */
