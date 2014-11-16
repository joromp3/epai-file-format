/* See LICENSE file for copyright and license terms. */

/* file_signature.h: header for file_signature.c */

#ifndef LIBEPAI_FILE_SIGNATURE_H
#define LIBEPAI_FILE_SIGNATURE_H


typedef struct {
	epai_section_type_t type;
} epai_fsign_section_t;


/** \fn epai_error_t epai_validate_file_signature_blob(const char* hdr, int len)
    \brief Validate a file signature header in memory.
    \param hdr Pointer to file signature header.
    \param len Length of file signature header (must be 11).
    \return EPAI_SUCCESS if valid, or the error if not.
*/
extern epai_error_t epai_validate_file_signature_blob(const char*, uint32_t);


/** \fn epai_error_t epai_new_file_signature_blob(const epai_fsign_section_t* ssp,
                                                  char** out, uint32_t* len)
    \brief Allocate new memory and generate a new file signature binary in it.
    \param ssp Pointer to section struct.
    \param out On success, will be set to a pointer to the new memory.
    \param len On success, will be set to the length of the new memory chunk.
    \return EPAI_SUCCESS on success, or some error.
*/
extern epai_error_t epai_new_file_signature_blob(const epai_fsign_section_t*,
						 char**, uint32_t*);


#endif /* LIBEPAI_FILE_SIGNATURE_H */

