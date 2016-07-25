#ifndef __libc_libc__
#define __libc_libc__

/* functions not defined elsewhere */

int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);

const char *_getprogname();

#endif
