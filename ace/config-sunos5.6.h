/* -*- C++ -*- */
// $Id$

// The following configuration file is designed to work for SunOS 5.6
// platforms using the SunC++ 4.x or g++ compilers.

#ifndef ACE_CONFIG_H

// ACE_CONFIG_H is defined by one of the following #included headers.

// #include the SunOS 5.5 config file, then add SunOS 5.6 updates below.

#include "ace/config-sunos5.5.h"

#if defined(__GNUC__) && __GNUC__ >= 2 && __GNUC_MINOR__ >= 95
// gcc-2.95 fixes this problem for us!
#undef ACE_HAS_STL_QUEUE_CONFLICT
#endif /* __GNUC__ */

#if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 199506L) || \
    defined (__EXTENSIONS__)
# define ACE_HAS_2_PARAM_ASCTIME_R_AND_CTIME_R
# define ACE_HAS_SIGWAIT
// Hack 'cuz -DPOSIX_SOURCE=199506L and -DEXTENSIONS hides this.
# include <sys/types.h>
  extern "C" int madvise(caddr_t, size_t, int);
#endif /* _POSIX_C_SOURCE >= 199506L  ||  __EXTENSIONS__ */

// SunOS 5.6 has AIO calls.
#if !defined (ACE_HAS_AIO_CALLS)
#define ACE_HAS_AIO_CALLS
#endif /* ACE_HAS_AIO_CALLS */

// Sunos 5.6's aio_* with RT signals is broken.
#define ACE_POSIX_AIOCB_PROACTOR

// SunOS 5.6 has a buggy select
#define ACE_HAS_LIMITED_SELECT

#endif /* ACE_CONFIG_H */
