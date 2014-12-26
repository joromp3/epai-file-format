/* See LICENSE file for copyright and license terms. */

/* checksum.h: header for checksum.c */


#ifndef LIBEPAI_CHECKSUM_H
#define LIBEPAI_CHECKSUM_H




typedef struct {
	epai_section_type_t type;
	uint32_t length;
	uint32_t checksum;
} epai_checksum_section_t;

/* free an existing checksum struct */
extern void epai_checksum_free_struct(epai_checksum_section_t*);

/* allocate a new checksum struct */
extern epai_error_t epai_checksum_new_struct(epai_checksum_section_t**);

/* validate a blob with encoded checksum data */
extern epai_error_t epai_checksum_validate_blob(const epai_byte_t*, uint32_t);

/* parse a checksum blob into a new struct */
extern epai_error_t epai_checksum_parse_blob(epai_checksum_section_t**,
		const epai_byte_t*, uint32_t);

/* encode a checksum section into an existing buffer */
extern epai_error_t epai_checksum_fill_blob(const epai_checksum_section_t*,
		epai_byte_t*, uint32_t);

/* encode a checksum section into a new buffer */
extern epai_error_t epai_checksum_new_blob(const epai_checksum_section_t*,
					  epai_byte_t**, uint32_t*);

/* return the length of the encoded checksum section at pointer */
extern uint32_t epai_checksum_parse_length(const epai_byte_t*);

/* return the length needed to encode checksum */
extern uint32_t epai_checksum_encode_length(const epai_checksum_section_t*);

/* calculate a crc32 sum */
uint32_t epai_crc32(uint32_t crc, const epai_byte_t *buf, size_t len);



#endif /* LIBEPAI_CHECKSUM_H */
