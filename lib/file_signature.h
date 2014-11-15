/* See LICENSE file for copyright and license terms. */

/* file_signature.h: header for file_signature.c */

#ifndef LIBEPAI_FILE_SIGNATURE_H
#define LIBEPAI_FILE_SIGNATURE_H


typedef struct {
	epai_section_type_t type;
} epai_file_signature_section_t;


/** \fn epai_error_t epai_validate_file_signature_blob(const char* hdr, int len)
    \brief Validate a file signature header in memory.
    \param hdr Pointer to file signature header.
    \param len Length of file signature header (must be 11).
    \return EPAI_SUCCESS if valid, or the error if not.
*/
extern epai_error_t epai_validate_file_signature_blob(const char*, uint32_t);

/** \fn epai_error_t epai_fill_file_signature_blob(char* buffer, uint32_t len)
    \brief Generate a file signature section header in existing memory.
    \param buffer Pointer to location to fill with the new header.
    \param len Length of header, for correctness. Must be exactly 11.
    \return EPAI_SUCCESS on success; EPAI_ERROR_SECTION_LENGTH if len invalid.
*/
extern epai_error_t epai_fill_file_signature_blob(char*, uint32_t);

/** \fn char* epai_new_file_signature_blob()
    \brief Allocate new memory and generate a new file signature header in it.
    \return Pointer to the new file signature section, or NULL on failure.
*/
extern char* epai_new_file_signature_blob();


#endif /* LIBEPAI_FILE_SIGNATURE_H */

