/* See LICENSE file for copyright and license terms. */

/* checksum.h: header for checksum.c */

#ifndef LIBEPAI_CHECKSUM_H
#define LIBEPAI_CHECKSUM_H


/** \fn uint32_t epai_crc32(uint32_t crc, const char *buf, size_t len)
    \brief Calculate checksum CRC32, like the one used in PNG.
    \param crc Initial value of the sum, used to continue from other sums.
    \param buf Pointer to buffer.
    \param len Length of buffer.
    \return crc32 sum.
*/
extern uint32_t epai_crc32(uint32_t crc, const char *buf, size_t len);



#endif /* LIBEPAI_CHECKSUM_H */
