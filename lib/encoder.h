/* See LICENSE file for copyright and license terms. */

/* encoder.h: encoding entire EPAI files. */


#ifndef LIBEPAI_ENCODER_H
#define LIBEPAI_ENCODER_H


typedef struct {
	epai_file_t* file;
} epai_encoder_t;


/* free encoder struct */
extern void epai_encoder_free(epai_encoder_t*, int);

/* create new encoder struct */
extern epai_error_t epai_encoder_new(epai_encoder_t**, epai_file_t*);

/* actually perform encoding process */
extern epai_error_t epai_encoder_encode_to_ptr(const epai_decoder_t*, char**);


#endif /* LIBEPAI_ENCODER_H */
