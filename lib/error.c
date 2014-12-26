/* See LICENSE file for copyright and license terms. */

/* error.c: error messages and reporting. */

#include "common.h"
#include "epai.h"

#define MSGLEN 256

static char errmsg[MSGLEN];


extern char* epai_get_error() {
	return errmsg;
}

extern void epai_set_error(const char* msg) {
	strncpy(errmsg, msg, MSGLEN - 1);
	/* ensure null termination */
	errmsg[MSGLEN-1] = 0;
}
