/* See LICENSE file for copyright and license terms. */

/* file.h: dealing with entire files. */


#ifndef EPAI_FILE_H
#define EPAI_FILE_H


typedef struct {
	epai_endian_t endian;
	int version;
	int num_sections;
	/* Pointers to all sections in their actual file order. */
	epai_section_t** sections;
} epai_file_t;


/* free file struct */
extern void epai_file_free(epai_file_t*);

/* create new file struct */
extern epai_error_t epai_file_new(epai_file_t** efp, epai_endian_t endian);

/* add a section to a file */
extern epai_error_t epai_file_add_section(epai_file_t* efp, epai_section_t* ssp);


#endif /* EPAI_FILE_H */