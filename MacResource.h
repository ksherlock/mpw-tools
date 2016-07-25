/*
 *
 * Macintosh Resource structures
 *
 */

#ifndef __MAC_RESOURCE__
#define __MAC_RESOURCE__

#include <stdint.h>

#define macresPreLoad	0x04
#define macresProtected	0x08
#define macresLocked	0x10
#define macresPurgeable	0x20
#define macresHeap	0x40

struct MacResourceHeader
{
	uint32_t offset_rdata;	/* offset to resource data */
	uint32_t offset_rmap;	/* offset to resource map  */
	uint32_t length_rdata;	/* length of resource data */
	uint32_t length_rmap;	/* length of resource map  */
};
typedef struct MacResourceHeader MacResourceHeader, *MacResourceHeaderPtr;


struct MacResourceMap
{
	uint8_t Reserved[16];		/* For system use */
	uint32_t NextResource;		/* For system use */
	uint16_t fileRef;			/* For system use */
	uint16_t attr;				/* resource fork attributes */
	uint16_t offset_typelist;	/* offset from map to typelist */
	uint16_t offset_namelist;	/* offset from map to namelist */
	uint16_t count;				/* # of resources -1 */
};
typedef struct MacResourceMap MacResourceMap, *MacResourceMapPtr;


struct MacResourceTypeList
{
	uint8_t ResourceType[4];
	uint16_t count;				/* # of resources -1 */
	uint16_t offset;			/* offset from typelist to ref. list */
};
typedef struct MacResourceTypeList MacResourceTypeList, *MacResourceTypeListPtr;

struct MacReferenceList
{
	uint16_t ResourceID;		/* ID of resource */
	uint16_t offset_namelist;	/* offset from reference list to name
								   or -1 for no name */
	uint8_t attr;				/* attributes */
	uint8_t offset_data[3];		/* offset from resource data to this data */
	uint32_t reserved;			/* for system use */

};
typedef struct MacReferenceList MacReferenceList, *MacReferenceListPtr;


#endif