#ifndef TOMCRYPT_H_
#define TOMCRYPT_H_
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>

/* use configuration data */
//#include <tomcrypt_custom.h>

#ifdef __cplusplus
extern "C" {
#endif

/* version */
#define CRYPT   0x0117
#define SCRYPT  "1.17"

/* max size of either a cipher/hash block or symmetric key [largest of the two] */
#define MAXBLOCKSIZE  128

/* descriptor table size */
#define TAB_SIZE      32

/* error codes [will be expanded in future releases] */
enum {
   CRYPT_OK=0,             /* Result OK */
   CRYPT_ERROR,            /* Generic Error */
   CRYPT_NOP,              /* Not a failure but no operation was performed */

   CRYPT_INVALID_KEYSIZE,  /* Invalid key size given */
   CRYPT_INVALID_ROUNDS,   /* Invalid number of rounds */
   CRYPT_FAIL_TESTVECTOR,  /* Algorithm failed test vectors */

   CRYPT_BUFFER_OVERFLOW,  /* Not enough space for output */
   CRYPT_INVALID_PACKET,   /* Invalid input packet given */

   CRYPT_INVALID_PRNGSIZE, /* Invalid number of bits for a PRNG */
   CRYPT_ERROR_READPRNG,   /* Could not read enough from PRNG */

   CRYPT_INVALID_CIPHER,   /* Invalid cipher specified */
   CRYPT_INVALID_HASH,     /* Invalid hash specified */
   CRYPT_INVALID_PRNG,     /* Invalid PRNG specified */

   CRYPT_MEM,              /* Out of memory */

   CRYPT_PK_TYPE_MISMATCH, /* Not equivalent types of PK keys */
   CRYPT_PK_NOT_PRIVATE,   /* Requires a private PK key */

   CRYPT_INVALID_ARG,      /* Generic invalid argument */
   CRYPT_FILE_NOTFOUND,    /* File Not Found */

   CRYPT_PK_INVALID_TYPE,  /* Invalid type of PK key */
   CRYPT_PK_INVALID_SYSTEM,/* Invalid PK system specified */
   CRYPT_PK_DUP,           /* Duplicate key already in key ring */
   CRYPT_PK_NOT_FOUND,     /* Key not found in keyring */
   CRYPT_PK_INVALID_SIZE,  /* Invalid size input for PK parameters */

   CRYPT_INVALID_PRIME_SIZE,/* Invalid size of prime requested */
   CRYPT_PK_INVALID_PADDING, /* Invalid padding on input */

   CRYPT_HASH_OVERFLOW      /* Hash applied to too many bits */
};

typedef unsigned long ulong64; // only used for length field, so ok.
typedef unsigned long ulong32;

#define LTC_MUTEX_PROTO(x)

#define STORE64L(x, y)                                                                     \
  do { (y)[7] = 0; (y)[6] = 0;   \
       (y)[5] = 0; (y)[4] = 0;   \
       (y)[3] = (unsigned char)(((x)>>24)&255); (y)[2] = (unsigned char)(((x)>>16)&255);   \
       (y)[1] = (unsigned char)(((x)>>8)&255); (y)[0] = (unsigned char)((x)&255); } while(0)

#define LOAD32L(x, y)                            \
  do { x = ((ulong32)((y)[3] & 255)<<24) | \
           ((ulong32)((y)[2] & 255)<<16) | \
           ((ulong32)((y)[1] & 255)<<8)  | \
           ((ulong32)((y)[0] & 255)); } while(0)

#define STORE32L(x, y)                                                                     \
  do { (y)[3] = (unsigned char)(((x)>>24)&255); (y)[2] = (unsigned char)(((x)>>16)&255);   \
       (y)[1] = (unsigned char)(((x)>>8)&255); (y)[0] = (unsigned char)((x)&255); } while(0)



#define XMEMCPY  memcpy

#ifndef MAX
   #define MAX(x, y) ( ((x)>(y))?(x):(y) )
#endif

#ifndef MIN
   #define MIN(x, y) ( ((x)<(y))?(x):(y) )
#endif

#define ROL(x, y) ( (((ulong32)(x)<<(ulong32)((y)&31)) | (((ulong32)(x)&0xFFFFFFFFUL)>>(ulong32)(32-((y)&31)))) & 0xFFFFFFFFUL)
#define ROR(x, y) ( ((((ulong32)(x)&0xFFFFFFFFUL)>>(ulong32)((y)&31)) | ((ulong32)(x)<<(ulong32)(32-((y)&31)))) & 0xFFFFFFFFUL)
#define ROLc(x, y) ( (((ulong32)(x)<<(ulong32)((y)&31)) | (((ulong32)(x)&0xFFFFFFFFUL)>>(ulong32)(32-((y)&31)))) & 0xFFFFFFFFUL)
#define RORc(x, y) ( ((((ulong32)(x)&0xFFFFFFFFUL)>>(ulong32)((y)&31)) | ((ulong32)(x)<<(ulong32)(32-((y)&31)))) & 0xFFFFFFFFUL)


/* fatal type of error */
#define LTC_ARGCHK(x) assert((x))
#define LTC_ARGCHKVD(x) LTC_ARGCHK(x)


#define LTC_MD2
#define LTC_MD4
#define LTC_MD5
#define LTC_SHA1

//#include <tomcrypt_cfg.h>
//#include <tomcrypt_macros.h>
//#include <tomcrypt_cipher.h>
#include <tomcrypt_hash.h>
//#include <tomcrypt_mac.h>
//#include <tomcrypt_prng.h>
//#include <tomcrypt_pk.h>
//#include <tomcrypt_math.h>
//#include <tomcrypt_misc.h>
//#include <tomcrypt_argchk.h>
//#include <tomcrypt_pkcs.h>

#ifdef __cplusplus
   }
#endif

#endif /* TOMCRYPT_H_ */


/* $Source$ */
/* $Revision$ */
/* $Date$ */