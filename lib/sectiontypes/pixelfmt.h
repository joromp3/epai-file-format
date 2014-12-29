/* See LICENSE file for copyright and license terms. */

/* image.h: definitions for EPAI image sections. */


#ifndef LIBEPAI_PIXELFMT_H
#define LIBEPAI_PIXELFMT_H


#define EPAI_PIXELFMT_MAX_CHANNELS 16


/* free an existing pixelfmt struct */
extern void epai_pixelfmt_free_struct(epai_pixelfmt_section_t*);

/* allocate a new pixelfmt struct */
extern epai_error_t epai_pixelfmt_new_struct(epai_pixelfmt_section_t**);

/* validate a blob with encoded pixelfmt data */
extern epai_error_t epai_pixelfmt_validate_blob(const epai_byte_t*, uint32_t);

/* parse a pixelfmt blob into a new struct */
extern epai_error_t epai_pixelfmt_parse_blob(epai_pixelfmt_section_t**,
		epai_file_t*, const epai_byte_t*, uint32_t);

/* encode a pixelfmt section into an existing buffer */
extern epai_error_t epai_pixelfmt_fill_blob(const epai_pixelfmt_section_t*,
		const epai_file_t*, epai_byte_t*, uint32_t);

/* encode a pixelfmt section into a new buffer */
extern epai_error_t epai_pixelfmt_new_blob(const epai_pixelfmt_section_t*,
		const epai_file_t*, epai_byte_t**, uint32_t*);

/* return the length of the encoded pixelfmt section at pointer */
extern uint32_t epai_pixelfmt_parse_length(const epai_file_t*, const epai_byte_t*);

/* return the length needed to encode pixelfmt */
extern uint32_t epai_pixelfmt_encode_length(const epai_pixelfmt_section_t*);


#endif /* LIBEPAI_PIXELFMT_H */
