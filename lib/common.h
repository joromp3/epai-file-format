/* See LICENSE file for copyright and license terms. */

/* common.h: common header for internal library source code. */

#ifndef LIBEPAI_COMMON_H
#define LIBEPAI_COMMON_H

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <sys/types.h>

#if STDC_HEADERS
#  include <stdlib.h>
#  include <string.h>
#elif HAVE_STRINGS_H
#  include <strings.h>
#endif /* STDC_HEADERS */

#if HAVE_UNISTD_H
#  include <unistd.h>
#endif


#endif /* LIBEPAI_COMMON_H */

