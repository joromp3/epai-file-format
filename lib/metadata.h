/* See LICENSE file for copyright and license terms. */

/* decoder.h: header for matadata.c */

#ifndef LIBEPAI_METADATA_H
#define LIBEPAI_METADATA_H


/** \fn epai_error_t epai_validate_metadata_blob(const char* buf, uint32_t len)
    \brief Validate a text metadata section in memory.
    \param buf Pointer to text metadata section.
    \param len Length of text metadata section, including section header.
    \return EPAI_SUCCESS if valid, or the error if not.
*/
extern epai_error_t epai_validate_metadata_blob(const char*, uint32_t);


#endif /* LIBEPAI_METADATA_H */
