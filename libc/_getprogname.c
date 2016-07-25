//#include <LowMem.h>
#include <string.h>

typedef unsigned char *StringPtr;
#define LMGetCurApName()    ((StringPtr) 0x0910)

const char *_getprogname() {
	static char buffer[32];
	StringPtr s = LMGetCurApName();
	unsigned i;

	if (!s) return "";

	i = s[0];
	if (i > 30) return "";
	memcpy(buffer, s + 1, i);
	s[i] = 0;
	return buffer;
}
