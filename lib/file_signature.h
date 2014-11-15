/* See LICENSE file for copyright and license terms. */

/* file_signature.h: header for file_signature.c */

#ifndef LIBEPAI_FILE_SIGNATURE_H
#define LIBEPAI_FILE_SIGNATURE_H


/** \fn epai_error_t epai_validate_file_signature(const char* hdr, int len)
    \brief Validate a file signature header in memory.
    \param hdr Pointer to file signature header.
    \param len Length of file signature header (must be 11).
    \return EPAI_SUCCESS if valid, or the error if not.
*/
extern epai_error_t epai_validate_file_signature(const char*, uint32_t);


#endif /* LIBEPAI_FILE_SIGNATURE_H */

