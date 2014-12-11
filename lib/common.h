/* See LICENSE file for copyright and license terms. */

/* common.h: common header for internal library source code. */

#ifndef LIBEPAI_COMMON_H
#define LIBEPAI_COMMON_H


#include <config.h>

#if HAVE_SYS_TYPES_H
#  include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */

#if HAVE_INTTYPES_H
#  include <inttypes.h>
#elif HAVE_STDINT_H
#  include <stdint.h>
#endif /* HAVE_INTTYPES_H */

#if HAVE_STDLIB_H
#  include <stdlib.h>
#endif /* HAVE_STDLIB_H */

#if HAVE_STRING_H
#  include <string.h>
#elif HAVE_STRINGS_H
#  include <strings.h>
#endif /* HAVE_STRING_H */

#if HAVE_MEMORY_H
#  include <memory.h>
#endif /* HAVE_MEMORY_H */

#if HAVE_ENDIAN_H
#  include <endian.h>
#endif /* HAVE_ENDIAN_H */

#if HAVE_UNISTD_H
#  include <unistd.h>
#endif /* HAVE_MEMORY_H */


#endif /* LIBEPAI_COMMON_H */

