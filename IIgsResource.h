#ifndef __IIGS_RESOURCE__
#define __IIGS_RESOURCE__

#include <stdint.h>

#define IIgsResChanged 0x0020
#define IIgsResPreLoad 0x0040
#define IIgsResProtected 0x0080
#define IIgsResAbsLoad 0x0400
#define IIgsResConverter 0x0800
#define IIgsResMemAttr 0xC31C               /* Flags passed to the NewHandle Memory Manager call */
#define IIgsSystemMap 0x0001
#define IIgsMapChanged 0x0002
#define IIgsRomMap 0x0004
#define IIgsResNameOffset 0x10000           /* type holding names */
#define IIgsResNameVersion 0x0001
#define IIgsSysFileID 0x0001


typedef uint32_t IIgsResID;
typedef uint16_t IIgsResType;
typedef uint16_t IIgsResAttr;

struct IIgsResHeaderRec {
	uint32_t rFileVersion;               /* Format version of resource fork */
	uint32_t rFileToMap;                 /* Offset from start to resource map record */
	uint32_t rFileMapSize;               /* Number of bytes map occupies in file */
	uint8_t rFileMemo[128];                 /* Reserved space for application */
};
typedef struct IIgsResHeaderRec IIgsResHeaderRec;

struct IIgsFreeBlockRec {
	uint32_t blkOffset;
	uint32_t blkSize;
};
typedef struct IIgsFreeBlockRec IIgsFreeBlockRec;

struct IIgsResMap {
	struct IIgsResMap **mapNext;             /* Handle to next resource map */
	uint16_t mapFlag;                        /* Bit Flags */
	uint32_t mapOffset;                  /* Map's file position */
	uint32_t mapSize;                    /* Number of bytes map occupies in file */
	uint16_t mapToIndex;
	uint16_t mapFileNum;
	uint16_t mapID;
	uint32_t mapIndexSize;
	uint32_t mapIndexUsed;
	uint16_t mapFreeListSize;
	uint16_t mapFreeListUsed;
	IIgsFreeBlockRec mapFreeList[1];         /* n bytes (array of free block records) */
};
typedef struct IIgsResMap IIgsResMap, *IIgsResMapPtr;

struct IIgsResRefRec {
	IIgsResType resType;
	IIgsResID resID;
	uint32_t resOffset;
	IIgsResAttr resAttr;
	uint32_t resSize;
	uint32_t resHandle;
};
typedef struct IIgsResRefRec IIgsResRefRec, *IIgsResRefRecPtr;

struct IIgsResourceSpec {
	IIgsResType resourceType;
	IIgsResID resourceID;
};
typedef struct IIgsResourceSpec IIgsResourceSpec;

#endif