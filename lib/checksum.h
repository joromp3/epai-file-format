/* See LICENSE file for copyright and license terms. */

/* checksum.h: header for checksum.c */


#ifndef LIBEPAI_CHECKSUM_H
#define LIBEPAI_CHECKSUM_H


/* calculate a crc32 sum */
extern uint32_t epai_crc32(uint32_t crc, const char *buf, size_t len);


#endif /* LIBEPAI_CHECKSUM_H */
