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
#include <Endian.h>

#include <stdint.h>
#include "IIgsResource.h"

// n.b. - all data is little endian.

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


const char *ResTypeName(uint16_t type)
{
	switch(type)
	{
	case 0x8001: return "rIcon";
	case 0x8002: return "rPicture";
	case 0x8003: return "rControlList";
	case 0x8004: return "rControlTemplate";
	case 0x8005: return "rC1InputString";
	case 0x8006: return "rPString";
	case 0x8007: return "rStringList";
	case 0x8008: return "rMenuBar";
	case 0x8009: return "rMenu";
	case 0x800A: return "rMenuItem";
	case 0x800B: return "rTextForLETextBox2";
	case 0x800C: return "rCtlDefProc";
	case 0x800D: return "rCtlColorTbl";
	case 0x800E: return "rWindParam1";
	case 0x800F: return "rWindParam2";
	case 0x8010: return "rWindColor";
	case 0x8011: return "rTextBlock";
	case 0x8012: return "rStyleBlock";
	case 0x8013: return "rToolStartup";
	case 0x8014: return "rResName";
	case 0x8015: return "rAlertString";
	case 0x8016: return "rText";
	case 0x8017: return "rCodeResource";
	case 0x8018: return "rCDEVCode";
	case 0x8019: return "rCDEVFlags";
	case 0x801A: return "rTwoRects";
	case 0x801B: return "rFileType";
	case 0x801C: return "rListRef";
	case 0x801D: return "rCString";
	case 0x801E: return "rXCMD";
	case 0x801F: return "rXFCN";
	case 0x8020: return "rErrorString";
	case 0x8021: return "rKTransTable";
	case 0x8022: return "rWString";
	case 0x8023: return "rC1OutputString";
	case 0x8024: return "rSoundSample";
	case 0x8025: return "rTERuler";
	case 0x8026: return "rFSequence";
	case 0x8027: return "rCursor";
	case 0x8028: return "rItemStruct";
	case 0x8029: return "rVersion";
	case 0x802A: return "rComment";
	case 0x802B: return "rBundle";
	case 0x802C: return "rFinderPath";
	case 0x802D: return "rPaletteWindow";
	case 0x802E: return "rTaggedStrings";
	case 0x802F: return "rPatternList";
	case 0xC001: return "rRectList";
	case 0xC002: return "rPrintRecord";
	case 0xC003: return "rFont";
	default: return NULL;
	}
}

int onefile(const char *file)
{
	int fd;
	ssize_t size;
	off_t off;

	IIgsResHeaderRec header;
	IIgsResMap map;
	uint8_t *mapdata;
	uint8_t *indexPtr;

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
		fprintf(stderr, "# %s: Not a IIgs resource fork.\n", file);
		close(fd);
		return -1;
	}

	header.rFileVersion = EndianU32_LtoN(header.rFileVersion);
	header.rFileToMap = EndianU32_LtoN(header.rFileToMap);
	header.rFileMapSize = EndianU32_LtoN(header.rFileMapSize);

	if (header.rFileVersion != 0x00000000)
	{
		fprintf(stderr, "# %s: Not a IIgs resource fork.\n", file);
		close(fd);
		return -1;
	}


	mapdata = malloc(header.rFileMapSize);
	if (!mapdata)
	{
		fprintf(stderr, "# %s Memory allocation failure: %s\n", file, strerror(errno));
		close(fd);
		return -1;			
	}


	off = lseek(fd, header.rFileToMap, SEEK_SET);
	if (off < 0)
	{
		fprintf(stderr, "# %s: Not a IIgs resource fork.\n", file);
		close(fd);
		free(mapdata);
		return -1;	
	}

	size = read(fd, mapdata, header.rFileMapSize);
	if (size < 0)
	{
		fprintf(stderr, "# %s Error reading file: %s\n", file, strerror(errno));
		close(fd);
		free(mapdata);
		return -1;		
	}
	if (size != header.rFileMapSize)
	{
		fprintf(stderr, "# %s: Not a IIgs resource fork.\n", file);
		close(fd);
		free(mapdata);
		return -1;		
	}

	memcpy(&map, mapdata, sizeof(map));

	// map.mapNext;
	map.mapFlag = EndianU16_LtoN(map.mapFlag);
	map.mapOffset = EndianU32_LtoN(map.mapOffset);
	map.mapSize = EndianU32_LtoN(map.mapSize);
	map.mapToIndex = EndianU16_LtoN(map.mapToIndex);
	map.mapFileNum = EndianU16_LtoN(map.mapFileNum);
	map.mapID = EndianU16_LtoN(map.mapID);
	map.mapIndexSize = EndianU32_LtoN(map.mapIndexSize);
	map.mapIndexUsed = EndianU32_LtoN(map.mapIndexUsed);
	map.mapFreeListSize = EndianU16_LtoN(map.mapFreeListSize);
	map.mapFreeListUsed = EndianU16_LtoN(map.mapFreeListUsed);

	indexPtr = mapdata + map.mapToIndex;


	printf("Type                       ID        Size    Attr\n");
	printf("-----                      --------- ------- -----\n");
	//      $8001 rIcon                $00000001 $0001c0 $0040
	for(;; indexPtr += sizeof(IIgsResRefRec))
	{
		IIgsResRefRec ref;
		const char *name;

		memcpy(&ref, indexPtr, sizeof(ref));
		if (!ref.resType) break;

		ref.resType = EndianU16_LtoN(ref.resType);
		ref.resID = EndianU32_LtoN(ref.resID);
		ref.resOffset = EndianU32_LtoN(ref.resOffset);
		ref.resAttr = EndianU16_LtoN(ref.resAttr);
		ref.resSize = EndianU32_LtoN(ref.resSize);
		//ref.resHandle


		name = ResTypeName(ref.resType);
		printf("$%04x %-20s $%08x $%06x $%04x\n",
			ref.resType,
			name ? name : "",
			ref.resID,
			ref.resSize,
			ref.resAttr
		);

	}


	return 0;
}

void help(int status)
{

	printf("# ListRezIIgs\n");
	printf("# Usage: ListRezIIgs [options] file");
	printf("#\n");

	exit(status);
}

int main(int argc, char **argv)
{

	// options for resID, resType, list only
	if (argc != 2)
		help(1);

	onefile(argv[1]);

	return 0;
}