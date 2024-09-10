
#ifndef MANTID_TYPES_DLL_H
#define MANTID_TYPES_DLL_H

#ifdef MANTID_TYPES_STATIC_DEFINE
#  define MANTID_TYPES_DLL
#  define MANTID_TYPES_NO_EXPORT
#else
#  ifndef MANTID_TYPES_DLL
#    ifdef Types_EXPORTS
        /* We are building this library */
#      define MANTID_TYPES_DLL __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define MANTID_TYPES_DLL __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef MANTID_TYPES_NO_EXPORT
#    define MANTID_TYPES_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef MANTID_TYPES_DEPRECATED
#  define MANTID_TYPES_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef MANTID_TYPES_DEPRECATED_EXPORT
#  define MANTID_TYPES_DEPRECATED_EXPORT MANTID_TYPES_DLL MANTID_TYPES_DEPRECATED
#endif

#ifndef MANTID_TYPES_DEPRECATED_NO_EXPORT
#  define MANTID_TYPES_DEPRECATED_NO_EXPORT MANTID_TYPES_NO_EXPORT MANTID_TYPES_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MANTID_TYPES_NO_DEPRECATED
#    define MANTID_TYPES_NO_DEPRECATED
#  endif
#endif

#ifndef UNUSED_ARG
    #define UNUSED_ARG(x) (void) x;
#endif

#ifndef TYPES_DEPRECATED
    #define TYPES_DEPRECATED(func) MANTID_TYPES_DEPRECATED func
#endif


#endif /* MANTID_TYPES_DLL_H */
