/* See LICENSE file for copyright and license terms. */

/* decoder.h: decoding entire EPAI files. */


#ifndef LIBEPAI_DECODER_H
#define LIBEPAI_DECODER_H


typedef struct {
	epai_file_t* file;
	const char* ptr_in;
	size_t buf_len;
} epai_decoder_t;


/* free decoder struct */
extern void epai_decoder_free(epai_decoder_t*);

/* create new decoder struct */
extern epai_error_t epai_decoder_new_from_ptr(epai_decoder_t**, const char*);

/* actually perform decoding process */
extern epai_error_t epai_decoder_decode(epai_decoder_t*);


#endif /* LIBEPAI_DECODER_H */
