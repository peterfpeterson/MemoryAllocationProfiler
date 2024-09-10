
#ifndef MANTID_KERNEL_DLL_H
#define MANTID_KERNEL_DLL_H

#ifdef MANTID_KERNEL_STATIC_DEFINE
#  define MANTID_KERNEL_DLL
#  define MANTID_KERNEL_NO_EXPORT
#else
#  ifndef MANTID_KERNEL_DLL
#    ifdef Kernel_EXPORTS
        /* We are building this library */
#      define MANTID_KERNEL_DLL __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define MANTID_KERNEL_DLL __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef MANTID_KERNEL_NO_EXPORT
#    define MANTID_KERNEL_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef MANTID_KERNEL_DEPRECATED
#  define MANTID_KERNEL_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef MANTID_KERNEL_DEPRECATED_EXPORT
#  define MANTID_KERNEL_DEPRECATED_EXPORT MANTID_KERNEL_DLL MANTID_KERNEL_DEPRECATED
#endif

#ifndef MANTID_KERNEL_DEPRECATED_NO_EXPORT
#  define MANTID_KERNEL_DEPRECATED_NO_EXPORT MANTID_KERNEL_NO_EXPORT MANTID_KERNEL_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MANTID_KERNEL_NO_DEPRECATED
#    define MANTID_KERNEL_NO_DEPRECATED
#  endif
#endif

#ifndef UNUSED_ARG
    #define UNUSED_ARG(x) (void) x;
#endif

#ifndef KERNEL_DEPRECATED
    #define KERNEL_DEPRECATED(func) MANTID_KERNEL_DEPRECATED func
#endif

// Use extern keyword in client code to suppress class template instantiation
#include "MantidKernel/System.h"

#ifdef Kernel_EXPORTS
#define EXTERN_MANTID_KERNEL
#else
#define EXTERN_MANTID_KERNEL EXTERN_IMPORT
#endif /* Kernel_EXPORTS*/

#endif /* MANTID_KERNEL_DLL_H */
