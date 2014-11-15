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


#endif /* LIBEPAI_PADDING_H */
