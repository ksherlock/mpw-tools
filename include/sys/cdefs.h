#ifndef _SYS_CDEFS_H_
#define _SYS_CDEFS_H_

#if defined(__cplusplus)
#define __BEGIN_DECLS   extern "C" {
#define __END_DECLS     }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif

#define __const const
#define __restrict
#define __signed signed
#define __volatile volatile
#if defined(__cplusplus)
#define __inline inline
#else
#define __inline
#endif

#define __dead2
#define __pure2
#define __unused
#define __used
#define __deprecated
#define __unavailable
#define __dead
#define __pure

#endif

