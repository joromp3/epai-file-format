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

/** \fn epai_error_t epai_fill_file_signature_blob(char* buffer,
                                                   epai_file_signature_t* ssp)
    \brief Generate a file signature section header binary in existing memory.
    \param buffer Pointer to location to fill with the new header.
    \param ssp Pointer to section struct.
    \return EPAI_SUCCESS on success.
*/
extern epai_error_t epai_fill_file_signature_blob(char*,
						  epai_file_signature_section_t*);

/** \fn char* epai_new_file_signature_blob()
    \brief Allocate new memory and generate a new file signature binary in it.
    \param ssp Pointer to section struct.
    \return Pointer to the new file signature binary, or NULL on failure.
*/
extern char* epai_new_file_signature_blob(epai_file_signature_section_t*);


#endif /* LIBEPAI_FILE_SIGNATURE_H */

