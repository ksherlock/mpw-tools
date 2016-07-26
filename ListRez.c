/*
 * Copyright (c) 2013, Kelvin W Sherlock
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sysexits.h>

#include <stdint.h>
#include <tomcrypt.h>

#include "MacResource.h"



// n.b. - all data is big endian.

int mflag = 0;

void hexdump(const uint8_t *data, ssize_t size)
{
const char *HexMap = "0123456789abcdef";

    char buffer1[16 * 3 + 1 + 1];
    char buffer2[16 + 1];
    ssize_t offset = 0;
    unsigned i, j;
    
    
    while(size > 0)
    {
        unsigned linelen = 16;

        memset(buffer1, ' ', sizeof(buffer1));
        memset(buffer2, ' ', sizeof(buffer2));
        
        if (size < linelen) linelen = size;
        
        
        for (i = 0, j = 0; i < linelen; i++)
        {
            unsigned x = data[i];
            buffer1[j++] = HexMap[x >> 4];
            buffer1[j++] = HexMap[x & 0x0f];
            j++;
            if (i == 7) j++;
            
            // isascii not part of std:: and may be a macro.
            buffer2[i] = isascii(x) && isprint(x) ? x : '.';
            
        }
        
        buffer1[sizeof(buffer1)-1] = 0;
        buffer2[sizeof(buffer2)-1] = 0;
        
    
        printf("%06x:\t%s\t%s\n", (unsigned)offset, buffer1, buffer2);

        offset += 16;
        data += 16;
        size -= 16;
    }

    printf("\n");
}

const char *unhash(const unsigned char *hash) {
	static char buffer[33];
	static char table[] = "0123456789abcdef";

	unsigned i, j;

	for (i = 0, j = 0; i < 16; ++i) {
		unsigned char c = hash[i];
		buffer[j++] = table[c >> 4];
		buffer[j++] = table[c & 0x0f];
	}
	buffer[j] = 0;
	return buffer;
}

const char *md5(int fd, uint32_t length) {
	hash_state md;
	static uint8_t buffer[4096];
	uint8_t hash[16];


	md5_init(&md);

	while (length) {
		long l;
		uint32_t count = sizeof(buffer);
		if (count > length) count = length;
		l = read(fd, buffer, count);

		if (l < 0) {
			if (errno == EINTR) continue;
			return NULL;
		}
		if (l == 0) break;

		md5_process(&md, buffer, l);

		length -= l;
	}
	if (length) return NULL;
	md5_done(&md, hash);
	return unhash(hash);
}

const char *TypeCode(uint8_t code[4])
{
	static char buffer[12];
	int ok = 1;
	int i;

	for (i = 0; i < 4; ++i)
	{
		if (isprint(code[i])) continue;

		sprintf(buffer, "$%02x%02x%02x%02x",
			code[0], code[1], code[2], code[3]);
		return buffer;
	}

	sprintf(buffer, "'%c%c%c%c'",
		code[0], code[1], code[2], code[3]);
	return buffer;
}

int onefile(const char *file)
{
	int fd;
	ssize_t size;
	off_t off;
	uint8_t *mapdata;
	uint8_t *typeListPtr;
	uint8_t *namePtr;
	int i, count;

	MacResourceHeader header;
	MacResourceMap map;


	fd = open(file, O_RDONLY | O_BINARY | O_RSRC);
	if (fd < 0)
	{
		fprintf(stderr, "# %s: Error opening file: %s\n", file, strerror(errno));
		return -1;
	}

	size = read(fd, &header, sizeof(header));
	if (size < 0)
	{
		fprintf(stderr, "# %s Error reading file: %s\n", file, strerror(errno));
		close(fd);
		return -1;
	}

	if (size < sizeof(header))
	{
		fprintf(stderr, "# %s: Not a macintosh resource fork.\n", file);
		close(fd);
		return -1;
	}

	// a couple sanity checks
	if (header.length_rmap == 0 || header.offset_rmap < sizeof(header))
	{
		fprintf(stderr, "# %s: Not a macintosh resource fork.\n", file);
		close(fd);
	}

	mapdata = malloc(header.length_rmap);
	if (!mapdata)
	{
		fprintf(stderr, "# %s Memory allocation failure: %s\n", file, strerror(errno));
		close(fd);
		return -1;			
	}


	off = lseek(fd, header.offset_rmap, SEEK_SET);
	if (off < 0)
	{
		fprintf(stderr, "# %s: Not a macintosh resource fork.\n", file);
		close(fd);
		free(mapdata);
		return -1;	
	}

	size = read(fd, mapdata, header.length_rmap);
	if (size < 0)
	{
		fprintf(stderr, "# %s Error reading file: %s\n", file, strerror(errno));
		close(fd);
		free(mapdata);
		return -1;		
	}
	if (size != header.length_rmap)
	{
		fprintf(stderr, "# %s: Not a macintosh resource fork.\n", file);
		close(fd);
		free(mapdata);
		return -1;		
	}

	memcpy(&map, mapdata, sizeof(map));

	typeListPtr = mapdata + map.offset_typelist + 2;
	namePtr = mapdata + map.offset_namelist;

	if (mflag) {
		printf("Type       ID    Size    Attr  Name             MD5\n");
		printf("-----      ----- ------- ----- ----             ---\n");
	}
	else {
		printf("Type       ID    Size    Attr  Name\n");
		printf("-----      ----- ------- ----- ----\n");
		//      'CODE'     $0004 $000018 $0020 SANELIB
	}
	// map.count is $ffff for an empty file.
	count = (map.count + 1) & 0xffff;
	for (i = 0; i < count; ++i, typeListPtr += sizeof(MacResourceTypeList))
	{
		MacResourceTypeList typeList;
		const char *tc;
		int j, count;

		uint8_t *refPtr;

		// todo -- should verify typListPtr, refPtr, namePtr are within the map.
		
		memcpy(&typeList, typeListPtr, sizeof(typeList));

		tc = TypeCode(typeList.ResourceType);

		refPtr = mapdata + map.offset_typelist + typeList.offset;
		count  = (typeList.count + 1) & 0xffff;
		for (j = 0; j < count; ++j, refPtr += sizeof(MacReferenceList))
		{
			MacReferenceList ref;
			char name[256];
			uint32_t rSize;
			uint32_t rOff;

			memcpy(&ref, refPtr, sizeof(ref));


			if (ref.offset_namelist != 0xffff)
			{
				int size = namePtr[ref.offset_namelist];
				memcpy(name, namePtr + ref.offset_namelist + 1, size);
				name[size] = 0;
			}
			else name[0] = 0;

			rSize = 0;
			// 24-bit ptr. yuck.
			
			rOff = (ref.offset_data[0] << 16)
				| (ref.offset_data[1] << 8)
				| (ref.offset_data[2] << 0);

			off = lseek(fd, header.offset_rdata + rOff, SEEK_SET);
			if (off < 0)
			{
				fprintf(stderr, "# %s: Not a macintosh resource fork.\n", file);
				close(fd);
				free(mapdata);
				return -1;
			}

			size = read(fd, &rSize, sizeof(rSize));
			if (size < 0)
			{
				fprintf(stderr, "# %s Error reading file: %s\n", file, strerror(errno));
				close(fd);
				free(mapdata);
				return -1;	
			}
			if (size != sizeof(rSize))
			{
				fprintf(stderr, "# %s: Not a macintosh resource fork.\n", file);
				close(fd);
				free(mapdata);
				return -1;		
			}


			if (mflag) {

				const char * hash = md5(fd, rSize);
				if (!hash) {
					fprintf(stderr, "# %s: Not a macintosh resource fork.\n", file);
					close(fd);
					free(mapdata);
					return -1;	
				}

				printf("%-10s $%04x $%06x $%04x %-16s %s\n", 
					tc, 
					ref.ResourceID,
					rSize,
					ref.attr,
					name,
					hash
				);
			}
			else {
				printf("%-10s $%04x $%06x $%04x %s\n", 
					tc, 
					ref.ResourceID,
					rSize,
					ref.attr,
					name
				);
			}
		}


	}


	return 0;
}

void help(int status)
{
	printf("# Usage: ListRez [-mh] file\n");

	exit(status);
}

int main(int argc, char **argv)
{
	int c;

	while((c = getopt(argc, argv, "hm")) != -1) {
		switch(c) {
			default:
			case ':':
			case '?':
				help(EX_USAGE);
				break;
			case 'h':
				help(0);
				break;
			case 'm':
				mflag = 1;
				break;
		}

	}

	argc -= optind;
	argv += optind;

	// options for resID, resType, list only
	if (argc != 1)
		help(EX_USAGE);

	onefile(*argv);

	return 0;
}