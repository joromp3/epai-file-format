/* See LICENSE file for copyright and license terms. */

/* file.c: dealing with entire files. */


#include "common.h"
#include "epai.h"


extern void epai_file_free(epai_file_t* efp) {
	int i;
	for (i = 0; i < efp->num_sections; ++i) {
		epai_section_free_struct(efp->sections[i]);
	}
	free(efp->sections);
	free(efp);
}

extern epai_error_t epai_file_new(epai_file_t** efp, epai_endian_t endian) {
	epai_file_t* nf;
	epai_error_t err;

	nf = malloc(sizeof(*nf));
	if (nf == NULL) {
		return EPAI_ERROR_MALLOC;
	}

	nf->endian = endian;
	nf->version = 0x00;
	nf->num_sections = 1;
	nf->sections = malloc(sizeof(*(nf->sections)));

	if (nf->sections == NULL) {
		free(nf);
		return EPAI_ERROR_MALLOC;
	}

	err = epai_file_signature_new_struct(nf->sections[0]);

	if (err) {
		free(nf->sections);
		free(nf);
		return err;
	}

	*efp = nf;

	return EPAI_SUCCESS;
}

extern epai_error_t epai_file_add_section(epai_file_t* efp, epai_section_t* ssp) {
	epai_section_t** tmp = realloc(efp->sections,
			(efp->num_sections + 1) * sizeof(*(efp->sections)));
	if (tmp == NULL) {
		return EPAI_ERROR_MALLOC;
	}

	efp->sections[efp->num_sections] = ssp;
	++efp->num_sections;

	return EPAI_SUCCESS;
}
