/* See LICENSE file for copyright and license terms. */

/* error.h: error messages and reporting. */

#ifndef LIBEPAI_ERROR_H
#define LIBEPAI_ERROR_H

typedef enum {
	/* No error. */
	EPAI_SUCCESS = 0,
	/* Undefined error (!EPAI_SUCCESS). */
	EPAI_ERROR_UNSPECIFIED,
	/* Out of memory. */
	EPAI_ERROR_MALLOC,
	/* Invalid operation. */
	EPAI_ERROR_BAD_OPERATION,
	/* Problem with file I/O. */
	EPAI_ERROR_FILEIO,
	/* Bad section type code. */
	EPAI_ERROR_SECTION_TYPE,
	/* Bad section length. */
	EPAI_ERROR_SECTION_LENGTH,
	/* Corrupt file signature. */
	EPAI_ERROR_BAD_FILE_SIGNATURE,
	/* Unsupported format version. */
	EPAI_ERROR_VERSION_UNSUPPORTED,
	/* Bad (nonzero) padding. */
	EPAI_ERROR_NONZERO_PADDING,
	/* Invalid metadata key string. */
	EPAI_ERROR_METADATA_KEY,
	/* Parts of metadata section exceed defined limits. */
	EPAI_ERROR_METADATA_LIMITS
} epai_error_t;


/* Get the message from the last error that occured. */
extern char* epai_get_error();

/* Set the current error message. */
extern void epai_set_error(const char*);

#endif /* LIBEPAI_ERROR_H */
