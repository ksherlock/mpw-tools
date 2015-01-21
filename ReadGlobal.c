#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int strcasecmp(const char *a, const char *b)
{
	for(; ; ++a, ++b) {
		char aa = *a;
		char bb = *b;

		aa = tolower(aa);
		bb = tolower(bb);

		if (aa == 0 || bb == 0)
		{
			if (aa) return 1;
			if (bb) return -1;
			return 0;
		}

		if (aa < bb) return -1;
		if (aa > bb) return 1;
	}
}

unsigned long GlobalAddress(const char *name, int *numeric)
{
	char *ep;
	unsigned long tmp;

	int len = name ? strlen(name) : 0;

	if (!len) return -1;

	// check for a number.

	switch (*name) {
		case '$':
			tmp = strtol(name + 1, &ep, 16);
			if (*ep == 0) { *numeric = 1; return tmp; }
			break;

		case '0':
			if (tolower(name[1]) == 'x') {
				tmp = strtol(name + 2, &ep, 16);
				if (*ep == 0) { *numeric = 1; return tmp; }
				break;
			}
			// fallthrough
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			tmp = strtol(name, &ep, 10);
			if (*ep == 0) { *numeric = 1; return tmp; }
			break;
	}	


	// sort ~/mpw/Globals.text | awk '{ printf("if (len == %d && strcasecmp(name, \"%s\") == 0) 
	// { return %s; }\n", length($1), $1, $3)  }'

	*numeric = 0;

	switch(tolower(*name))
	{
		case 'a':
if (len == 7 && strcasecmp(name, "ABusDCE") == 0) { return 0x2DC; }
if (len == 8 && strcasecmp(name, "ABusVars") == 0) { return 0x2D8; }
if (len == 7 && strcasecmp(name, "ADBBase") == 0) { return 0x0CF8; }
if (len == 7 && strcasecmp(name, "ASCBase") == 0) { return 0x0CC0; }
if (len == 10 && strcasecmp(name, "AlarmState") == 0) { return 0x21F; }
if (len == 9 && strcasecmp(name, "ApplLimit") == 0) { return 0x130; }
if (len == 8 && strcasecmp(name, "ApplZone") == 0) { return 0x2AA; }
		break;
		case 'b':
if (len == 9 && strcasecmp(name, "BootDrive") == 0) { return 0x210; }
if (len == 6 && strcasecmp(name, "BufPtr") == 0) { return 0x10C; }
if (len == 9 && strcasecmp(name, "BufTgDate") == 0) { return 0x304; }
if (len == 11 && strcasecmp(name, "BufTgFBkNum") == 0) { return 0x302; }
if (len == 9 && strcasecmp(name, "BufTgFFlg") == 0) { return 0x300; }
if (len == 9 && strcasecmp(name, "BufTgFNum") == 0) { return 0x2FC; }
if (len == 9 && strcasecmp(name, "BusErrVct") == 0) { return 0x08; }
		break;
		case 'c':
if (len == 7 && strcasecmp(name, "CPUFlag") == 0) { return 0x12F; }
if (len == 10 && strcasecmp(name, "CQDGlobals") == 0) { return 0x0CCC; }
if (len == 9 && strcasecmp(name, "CaretTime") == 0) { return 0x2F4; }
if (len == 11 && strcasecmp(name, "ChunkyDepth") == 0) { return 0x0D60; }
if (len == 8 && strcasecmp(name, "ColLines") == 0) { return 0x0C22; }
if (len == 18 && strcasecmp(name, "CommToolboxGlobals") == 0) { return 0x0BB4; }
if (len == 8 && strcasecmp(name, "CrsrAddr") == 0) { return 0x888; }
if (len == 8 && strcasecmp(name, "CrsrBase") == 0) { return 0x898; }
if (len == 8 && strcasecmp(name, "CrsrBusy") == 0) { return 0x8CD; }
if (len == 10 && strcasecmp(name, "CrsrCouple") == 0) { return 0x8CF; }
if (len == 10 && strcasecmp(name, "CrsrDevice") == 0) { return 0x89C; }
if (len == 7 && strcasecmp(name, "CrsrNew") == 0) { return 0x8CE; }
if (len == 11 && strcasecmp(name, "CrsrObscure") == 0) { return 0x8D2; }
if (len == 7 && strcasecmp(name, "CrsrPin") == 0) { return 0x834; }
if (len == 7 && strcasecmp(name, "CrsrPtr") == 0) { return 0x0D62; }
if (len == 8 && strcasecmp(name, "CrsrRect") == 0) { return 0x83C; }
if (len == 7 && strcasecmp(name, "CrsrRow") == 0) { return 0x8AC; }
if (len == 8 && strcasecmp(name, "CrsrSave") == 0) { return 0x88C; }
if (len == 9 && strcasecmp(name, "CrsrScale") == 0) { return 0x8D3; }
if (len == 9 && strcasecmp(name, "CrsrState") == 0) { return 0x8D0; }
if (len == 10 && strcasecmp(name, "CrsrThresh") == 0) { return 0x8EC; }
if (len == 7 && strcasecmp(name, "CrsrVis") == 0) { return 0x8CC; }
if (len == 11 && strcasecmp(name, "CurActivate") == 0) { return 0xA64; }
if (len == 9 && strcasecmp(name, "CurApName") == 0) { return 0x910; }
if (len == 11 && strcasecmp(name, "CurApRefNum") == 0) { return 0x900; }
if (len == 11 && strcasecmp(name, "CurDeactive") == 0) { return 0xA68; }
if (len == 11 && strcasecmp(name, "CurDirStore") == 0) { return 0x398; }
if (len == 11 && strcasecmp(name, "CurJTOffset") == 0) { return 0x934; }
if (len == 6 && strcasecmp(name, "CurMap") == 0) { return 0xA5A; }
if (len == 13 && strcasecmp(name, "CurPageOption") == 0) { return 0x936; }
if (len == 8 && strcasecmp(name, "CurPitch") == 0) { return 0x280; }
if (len == 12 && strcasecmp(name, "CurStackBase") == 0) { return 0x908; }
if (len == 9 && strcasecmp(name, "CurrentA5") == 0) { return 0x904; }
		break;
		case 'd':
if (len == 11 && strcasecmp(name, "DSAlertRect") == 0) { return 0x3F8; }
if (len == 10 && strcasecmp(name, "DSAlertTab") == 0) { return 0x2BA; }
if (len == 8 && strcasecmp(name, "DSCtrAdj") == 0) { return 0x0DA8; }
if (len == 10 && strcasecmp(name, "DSDrawProc") == 0) { return 0x334; }
if (len == 9 && strcasecmp(name, "DSErrCode") == 0) { return 0xAF0; }
if (len == 11 && strcasecmp(name, "DSWndUpdate") == 0) { return 0x15D; }
if (len == 8 && strcasecmp(name, "DTQFlags") == 0) { return 0x0D92; }
if (len == 7 && strcasecmp(name, "DTQueue") == 0) { return 0x0D92; }
if (len == 8 && strcasecmp(name, "DTskQHdr") == 0) { return 0x0D94; }
if (len == 9 && strcasecmp(name, "DTskQTail") == 0) { return 0x0D98; }
if (len == 10 && strcasecmp(name, "DefltStack") == 0) { return 0x322; }
if (len == 8 && strcasecmp(name, "DeskHook") == 0) { return 0xA6C; }
if (len == 11 && strcasecmp(name, "DeskPattern") == 0) { return 0xA3C; }
if (len == 10 && strcasecmp(name, "DeviceList") == 0) { return 0x8A8; }
if (len == 10 && strcasecmp(name, "DoubleTime") == 0) { return 0x2F0; }
if (len == 8 && strcasecmp(name, "DragHook") == 0) { return 0x9F6; }
if (len == 7 && strcasecmp(name, "DrvQHdr") == 0) { return 0x308; }
if (len == 6 && strcasecmp(name, "DskErr") == 0) { return 0x142; }
if (len == 9 && strcasecmp(name, "DskVerify") == 0) { return 0x12C; }
		break;
		case 'e':
if (len == 11 && strcasecmp(name, "EjectNotify") == 0) { return 0x338; }
if (len == 9 && strcasecmp(name, "EndSRTPtr") == 0) { return 0x0DB4; }
if (len == 10 && strcasecmp(name, "EventQueue") == 0) { return 0x14A; }
if (len == 9 && strcasecmp(name, "EvtBufCnt") == 0) { return 0x154; }
if (len == 9 && strcasecmp(name, "ExpandMem") == 0) { return 0x2B6; }
if (len == 8 && strcasecmp(name, "ExtStsDT") == 0) { return 0x2BE; }
		break;
		case 'g':
if (len == 9 && strcasecmp(name, "GZMoveHnd") == 0) { return 0x330; }
if (len == 9 && strcasecmp(name, "GZRootHnd") == 0) { return 0x328; }
if (len == 9 && strcasecmp(name, "GZRootPtr") == 0) { return 0x32C; }
if (len == 8 && strcasecmp(name, "GetParam") == 0) { return 0x1E4; }
if (len == 11 && strcasecmp(name, "GhostWindow") == 0) { return 0xA84; }
if (len == 7 && strcasecmp(name, "GrayRgn") == 0) { return 0x9EE; }
		break;
		case 'h':
if (len == 7 && strcasecmp(name, "HeapEnd") == 0) { return 0x114; }
if (len == 10 && strcasecmp(name, "HiHeapMark") == 0) { return 0xBAE; }
if (len == 9 && strcasecmp(name, "HiKeyLast") == 0) { return 0x216; }
if (len == 10 && strcasecmp(name, "HiliteMode") == 0) { return 0x938; }
if (len == 9 && strcasecmp(name, "HiliteRGB") == 0) { return 0x0DA0; }
if (len == 5 && strcasecmp(name, "HpChk") == 0) { return 0x316; }
		break;
		case 'i':
if (len == 9 && strcasecmp(name, "IAZNotify") == 0) { return 0x33C; }
if (len == 3 && strcasecmp(name, "IWM") == 0) { return 0x1E0; }
if (len == 10 && strcasecmp(name, "IconTLAddr") == 0) { return 0x0DAC; }
if (len == 7 && strcasecmp(name, "IntFlag") == 0) { return 0x15F; }
if (len == 8 && strcasecmp(name, "IntlSpec") == 0) { return 0xBA0; }
		break;
		case 'j':
if (len == 10 && strcasecmp(name, "JAllocCrsr") == 0) { return 0x88C; }
if (len == 9 && strcasecmp(name, "JCrsrTask") == 0) { return 0x8EE; }
if (len == 10 && strcasecmp(name, "JDTInstall") == 0) { return 0x0D9C; }
if (len == 6 && strcasecmp(name, "JFetch") == 0) { return 0x8F4; }
if (len == 10 && strcasecmp(name, "JGNEFilter") == 0) { return 0x29A; }
if (len == 7 && strcasecmp(name, "JIODone") == 0) { return 0x8FC; }
if (len == 9 && strcasecmp(name, "JKybdTask") == 0) { return 0x21A; }
if (len == 11 && strcasecmp(name, "JOpcodeProc") == 0) { return 0x894; }
if (len == 9 && strcasecmp(name, "JSetCCrsr") == 0) { return 0x890; }
if (len == 6 && strcasecmp(name, "JStash") == 0) { return 0x8F8; }
if (len == 8 && strcasecmp(name, "JSwapMMU") == 0) { return 0x0DBC; }
if (len == 8 && strcasecmp(name, "JVBLTask") == 0) { return 0x0D28; }
if (len == 11 && strcasecmp(name, "JournalFlag") == 0) { return 0x8DE; }
if (len == 10 && strcasecmp(name, "JournalRef") == 0) { return 0x8E8; }
		break;
		case 'k':
if (len == 7 && strcasecmp(name, "KbdLast") == 0) { return 0x218; }
if (len == 7 && strcasecmp(name, "KbdType") == 0) { return 0x21E; }
if (len == 7 && strcasecmp(name, "KbdVars") == 0) { return 0x216; }
if (len == 9 && strcasecmp(name, "Key1Trans") == 0) { return 0x29E; }
if (len == 9 && strcasecmp(name, "Key2Trans") == 0) { return 0x2A2; }
if (len == 7 && strcasecmp(name, "KeyLast") == 0) { return 0x184; }
if (len == 8 && strcasecmp(name, "KeyMVars") == 0) { return 0xB04; }
if (len == 8 && strcasecmp(name, "KeyMapLM") == 0) { return 0x174; }
if (len == 12 && strcasecmp(name, "KeyRepThresh") == 0) { return 0x190; }
if (len == 10 && strcasecmp(name, "KeyRepTime") == 0) { return 0x18A; }
if (len == 9 && strcasecmp(name, "KeyThresh") == 0) { return 0x18E; }
if (len == 7 && strcasecmp(name, "KeyTime") == 0) { return 0x186; }
if (len == 9 && strcasecmp(name, "KeypadMap") == 0) { return 0x17C; }
		break;
		case 'l':
if (len == 13 && strcasecmp(name, "LastTxGDevice") == 0) { return 0x0DC4; }
if (len == 10 && strcasecmp(name, "LaunchFlag") == 0) { return 0x902; }
if (len == 8 && strcasecmp(name, "Lo3Bytes") == 0) { return 0x31A; }
if (len == 8 && strcasecmp(name, "LoadTrap") == 0) { return 0x12D; }
if (len == 12 && strcasecmp(name, "LoaderPBlock") == 0) { return 0x93A; }
if (len == 6 && strcasecmp(name, "Lvl1DT") == 0) { return 0x192; }
if (len == 6 && strcasecmp(name, "Lvl2DT") == 0) { return 0x1B2; }
		break;
		case 'm':
if (len == 7 && strcasecmp(name, "MBState") == 0) { return 0x172; }
if (len == 7 && strcasecmp(name, "MBTicks") == 0) { return 0x16E; }
if (len == 10 && strcasecmp(name, "MBarHeight") == 0) { return 0xBAA; }
if (len == 10 && strcasecmp(name, "MMDefFlags") == 0) { return 0x326; }
if (len == 8 && strcasecmp(name, "MMU32bit") == 0) { return 0x0CB2; }
if (len == 8 && strcasecmp(name, "MMUFlags") == 0) { return 0x0CB0; }
if (len == 8 && strcasecmp(name, "MMUFluff") == 0) { return 0x0CB3; }
if (len == 6 && strcasecmp(name, "MMUTbl") == 0) { return 0x0CB4; }
if (len == 10 && strcasecmp(name, "MMUTblSize") == 0) { return 0x0CB8; }
if (len == 7 && strcasecmp(name, "MMUType") == 0) { return 0x0CB1; }
if (len == 5 && strcasecmp(name, "MTemp") == 0) { return 0x828; }
if (len == 10 && strcasecmp(name, "MainDevice") == 0) { return 0x8A4; }
if (len == 6 && strcasecmp(name, "MaskBC") == 0) { return 0x31A; }
if (len == 10 && strcasecmp(name, "MaskHandle") == 0) { return 0x31A; }
if (len == 7 && strcasecmp(name, "MaskPtr") == 0) { return 0x31A; }
if (len == 6 && strcasecmp(name, "MemErr") == 0) { return 0x220; }
if (len == 6 && strcasecmp(name, "MemTop") == 0) { return 0x108; }
if (len == 11 && strcasecmp(name, "MickeyBytes") == 0) { return 0x0D6A; }
if (len == 8 && strcasecmp(name, "MinStack") == 0) { return 0x31E; }
if (len == 8 && strcasecmp(name, "MinusOne") == 0) { return 0xA06; }
if (len == 6 && strcasecmp(name, "MmInOK") == 0) { return 0x12E; }
if (len == 11 && strcasecmp(name, "MonkeyLives") == 0) { return 0x100; }
if (len == 5 && strcasecmp(name, "Mouse") == 0) { return 0x830; }
if (len == 9 && strcasecmp(name, "MouseMask") == 0) { return 0x8D6; }
if (len == 11 && strcasecmp(name, "MouseOffset") == 0) { return 0x8DA; }
		break;
		case 'n':
if (len == 7 && strcasecmp(name, "NMIFlag") == 0) { return 0x0C2C; }
if (len == 11 && strcasecmp(name, "NewCrsrJTbl") == 0) { return 0x88C; }
		break;
		case 'o':
if (len == 6 && strcasecmp(name, "OneOne") == 0) { return 0xA02; }
		break;
		case 'p':
if (len == 9 && strcasecmp(name, "PCDeskPat") == 0) { return 0x20B; }
if (len == 7 && strcasecmp(name, "PWMBuf2") == 0) { return 0x312; }
if (len == 10 && strcasecmp(name, "PaintWhite") == 0) { return 0x9DC; }
if (len == 8 && strcasecmp(name, "PortAUse") == 0) { return 0x290; }
if (len == 8 && strcasecmp(name, "PortBUse") == 0) { return 0x291; }
if (len == 8 && strcasecmp(name, "PortList") == 0) { return 0x0D66; }
		break;
		case 'q':
if (len == 8 && strcasecmp(name, "QDColors") == 0) { return 0x8B0; }
if (len == 7 && strcasecmp(name, "QDErrLM") == 0) { return 0x0D6E; }
if (len == 7 && strcasecmp(name, "QDExist") == 0) { return 0x8F3; }
		break;
		case 'r':
if (len == 7 && strcasecmp(name, "RAMBase") == 0) { return 0x2B2; }
if (len == 8 && strcasecmp(name, "RGBBlack") == 0) { return 0x0C10; }
if (len == 8 && strcasecmp(name, "RGBWhite") == 0) { return 0x0C16; }
if (len == 5 && strcasecmp(name, "ROM85") == 0) { return 0x28E; }
if (len == 7 && strcasecmp(name, "ROMBase") == 0) { return 0x2AE; }
if (len == 10 && strcasecmp(name, "ROMMapHndl") == 0) { return 0xB06; }
if (len == 8 && strcasecmp(name, "RawMouse") == 0) { return 0x82C; }
if (len == 6 && strcasecmp(name, "ResErr") == 0) { return 0xA60; }
if (len == 10 && strcasecmp(name, "ResErrProc") == 0) { return 0xAF2; }
if (len == 7 && strcasecmp(name, "ResLoad") == 0) { return 0xA5E; }
if (len == 11 && strcasecmp(name, "ResReadOnly") == 0) { return 0xA5C; }
if (len == 8 && strcasecmp(name, "RestProc") == 0) { return 0xA8C; }
if (len == 10 && strcasecmp(name, "ResumeProc") == 0) { return 0xA8C; }
if (len == 7 && strcasecmp(name, "RndSeed") == 0) { return 0x156; }
if (len == 12 && strcasecmp(name, "RomMapInsert") == 0) { return 0xB9E; }
if (len == 7 && strcasecmp(name, "RowBits") == 0) { return 0x0C20; }
		break;
		case 's':
if (len == 7 && strcasecmp(name, "SCCASts") == 0) { return 0x2CE; }
if (len == 7 && strcasecmp(name, "SCCBSts") == 0) { return 0x2CF; }
if (len == 5 && strcasecmp(name, "SCCRd") == 0) { return 0x1D8; }
if (len == 5 && strcasecmp(name, "SCCWr") == 0) { return 0x1DC; }
if (len == 8 && strcasecmp(name, "SCSIBase") == 0) { return 0x0C00; }
if (len == 7 && strcasecmp(name, "SCSIDMA") == 0) { return 0x0C04; }
if (len == 11 && strcasecmp(name, "SCSIGlobals") == 0) { return 0x0C0C; }
if (len == 7 && strcasecmp(name, "SCSIHsk") == 0) { return 0x0C08; }
if (len == 8 && strcasecmp(name, "SCSIPoll") == 0) { return 0x0C2F; }
if (len == 12 && strcasecmp(name, "SDMJmpTblPtr") == 0) { return 0x0DB8; }
if (len == 9 && strcasecmp(name, "SEVarBase") == 0) { return 0x0C30; }
if (len == 7 && strcasecmp(name, "SEvtEnb") == 0) { return 0x15C; }
if (len == 10 && strcasecmp(name, "SFSaveDisk") == 0) { return 0x214; }
if (len == 8 && strcasecmp(name, "SInfoPtr") == 0) { return 0x0CBC; }
if (len == 10 && strcasecmp(name, "SInitFlags") == 0) { return 0x0D90; }
if (len == 9 && strcasecmp(name, "SMGlobals") == 0) { return 0x0CC4; }
if (len == 8 && strcasecmp(name, "SPATalkA") == 0) { return 0x1F9; }
if (len == 8 && strcasecmp(name, "SPATalkB") == 0) { return 0x1FA; }
if (len == 7 && strcasecmp(name, "SPAlarm") == 0) { return 0x200; }
if (len == 11 && strcasecmp(name, "SPClikCaret") == 0) { return 0x209; }
if (len == 8 && strcasecmp(name, "SPConfig") == 0) { return 0x1FB; }
if (len == 6 && strcasecmp(name, "SPFont") == 0) { return 0x204; }
if (len == 5 && strcasecmp(name, "SPKbd") == 0) { return 0x206; }
if (len == 7 && strcasecmp(name, "SPMisc1") == 0) { return 0x20A; }
if (len == 7 && strcasecmp(name, "SPMisc2") == 0) { return 0x20B; }
if (len == 7 && strcasecmp(name, "SPPortA") == 0) { return 0x1FC; }
if (len == 7 && strcasecmp(name, "SPPortB") == 0) { return 0x1FE; }
if (len == 7 && strcasecmp(name, "SPPrint") == 0) { return 0x207; }
if (len == 7 && strcasecmp(name, "SPValid") == 0) { return 0x1F8; }
if (len == 8 && strcasecmp(name, "SPVolCtl") == 0) { return 0x208; }
if (len == 11 && strcasecmp(name, "SRsrcTblPtr") == 0) { return 0x0D24; }
if (len == 13 && strcasecmp(name, "SaveSegHandle") == 0) { return 0x930; }
if (len == 9 && strcasecmp(name, "ScrDmpEnb") == 0) { return 0x2F8; }
if (len == 10 && strcasecmp(name, "ScrDmpType") == 0) { return 0x2F9; }
if (len == 7 && strcasecmp(name, "ScrHRes") == 0) { return 0x104; }
if (len == 7 && strcasecmp(name, "ScrVRes") == 0) { return 0x102; }
if (len == 10 && strcasecmp(name, "ScrapCount") == 0) { return 0x968; }
if (len == 8 && strcasecmp(name, "ScrapEnd") == 0) { return 0x980; }
if (len == 11 && strcasecmp(name, "ScrapHandle") == 0) { return 0x964; }
if (len == 9 && strcasecmp(name, "ScrapInfo") == 0) { return 0x960; }
if (len == 9 && strcasecmp(name, "ScrapName") == 0) { return 0x96C; }
if (len == 9 && strcasecmp(name, "ScrapSize") == 0) { return 0x960; }
if (len == 10 && strcasecmp(name, "ScrapState") == 0) { return 0x96A; }
if (len == 8 && strcasecmp(name, "ScrapTag") == 0) { return 0x970; }
if (len == 9 && strcasecmp(name, "ScrapVars") == 0) { return 0x960; }
if (len == 9 && strcasecmp(name, "Scratch20") == 0) { return 0x1E4; }
if (len == 8 && strcasecmp(name, "Scratch8") == 0) { return 0x9FA; }
if (len == 11 && strcasecmp(name, "ScreenBytes") == 0) { return 0x0C24; }
if (len == 9 && strcasecmp(name, "ScreenRow") == 0) { return 0x106; }
if (len == 8 && strcasecmp(name, "ScrnBase") == 0) { return 0x824; }
if (len == 10 && strcasecmp(name, "ScrnVBLPtr") == 0) { return 0x0D10; }
if (len == 8 && strcasecmp(name, "SdVolume") == 0) { return 0x260; }
if (len == 9 && strcasecmp(name, "SdmBusErr") == 0) { return 0x0DC0; }
if (len == 11 && strcasecmp(name, "SegHiEnable") == 0) { return 0xBB2; }
if (len == 10 && strcasecmp(name, "SerialVars") == 0) { return 0x2D0; }
if (len == 9 && strcasecmp(name, "SlotPrTbl") == 0) { return 0x0D08; }
if (len == 7 && strcasecmp(name, "SlotQDT") == 0) { return 0x0D04; }
if (len == 9 && strcasecmp(name, "SlotTICKS") == 0) { return 0x0D14; }
if (len == 8 && strcasecmp(name, "SlotVBLQ") == 0) { return 0x0D0C; }
if (len == 11 && strcasecmp(name, "SoundActive") == 0) { return 0x27E; }
if (len == 9 && strcasecmp(name, "SoundBase") == 0) { return 0x266; }
if (len == 8 && strcasecmp(name, "SoundDCE") == 0) { return 0x27A; }
if (len == 10 && strcasecmp(name, "SoundLevel") == 0) { return 0x27F; }
if (len == 8 && strcasecmp(name, "SoundPtr") == 0) { return 0x262; }
if (len == 8 && strcasecmp(name, "SoundVBL") == 0) { return 0x26A; }
if (len == 9 && strcasecmp(name, "SrcDevice") == 0) { return 0x8A0; }
if (len == 8 && strcasecmp(name, "StkLowPt") == 0) { return 0x110; }
if (len == 12 && strcasecmp(name, "SwitcherTPtr") == 0) { return 0x286; }
if (len == 9 && strcasecmp(name, "SysEvtBuf") == 0) { return 0x146; }
if (len == 10 && strcasecmp(name, "SysEvtMask") == 0) { return 0x144; }
if (len == 6 && strcasecmp(name, "SysMap") == 0) { return 0xA58; }
if (len == 10 && strcasecmp(name, "SysMapHndl") == 0) { return 0xA54; }
if (len == 8 && strcasecmp(name, "SysParam") == 0) { return 0x1F8; }
if (len == 10 && strcasecmp(name, "SysResName") == 0) { return 0xAD8; }
if (len == 10 && strcasecmp(name, "SysVersion") == 0) { return 0x15A; }
if (len == 7 && strcasecmp(name, "SysZone") == 0) { return 0x2A6; }
		break;
		case 't':
if (len == 8 && strcasecmp(name, "TEDoText") == 0) { return 0xA70; }
if (len == 7 && strcasecmp(name, "TERecal") == 0) { return 0xA74; }
if (len == 12 && strcasecmp(name, "TEScrpHandle") == 0) { return 0xAB4; }
if (len == 12 && strcasecmp(name, "TEScrpLength") == 0) { return 0xAB0; }
if (len == 9 && strcasecmp(name, "TESysJust") == 0) { return 0xBAC; }
if (len == 9 && strcasecmp(name, "TEWdBreak") == 0) { return 0xAF6; }
if (len == 9 && strcasecmp(name, "TableSeed") == 0) { return 0x0D20; }
if (len == 7 && strcasecmp(name, "TagData") == 0) { return 0x2FA; }
if (len == 7 && strcasecmp(name, "TheCrsr") == 0) { return 0x844; }
if (len == 10 && strcasecmp(name, "TheGDevice") == 0) { return 0x0CC8; }
if (len == 7 && strcasecmp(name, "TheZone") == 0) { return 0x118; }
if (len == 5 && strcasecmp(name, "Ticks") == 0) { return 0x16A; }
if (len == 8 && strcasecmp(name, "TimeDBRA") == 0) { return 0x0D00; }
if (len == 6 && strcasecmp(name, "TimeLM") == 0) { return 0x20C; }
if (len == 9 && strcasecmp(name, "TimeSCCDB") == 0) { return 0x0D02; }
if (len == 10 && strcasecmp(name, "TimeSCSIDB") == 0) { return 0x0DA6; }
if (len == 10 && strcasecmp(name, "TmpResLoad") == 0) { return 0xB9F; }
if (len == 10 && strcasecmp(name, "TopMapHndl") == 0) { return 0xA50; }
		break;
		case 'u':
if (len == 10 && strcasecmp(name, "UTableBase") == 0) { return 0x11C; }
if (len == 11 && strcasecmp(name, "UnitNtryCnt") == 0) { return 0x1D2; }
		break;
		case 'v':
if (len == 8 && strcasecmp(name, "VBLQueue") == 0) { return 0x160; }
if (len == 3 && strcasecmp(name, "VIA") == 0) { return 0x1D4; }
if (len == 6 && strcasecmp(name, "VIA2DT") == 0) { return 0x0D70; }
if (len == 9 && strcasecmp(name, "VertRRate") == 0) { return 0x0D30; }
if (len == 7 && strcasecmp(name, "VidMode") == 0) { return 0x0C2E; }
if (len == 7 && strcasecmp(name, "VidType") == 0) { return 0x0C2D; }
if (len == 11 && strcasecmp(name, "VideoInfoOK") == 0) { return 0x0DB0; }
		break;
		case 'w':
if (len == 9 && strcasecmp(name, "WMgrCPort") == 0) { return 0x0D2C; }
if (len == 8 && strcasecmp(name, "WMgrPort") == 0) { return 0x9DE; }
if (len == 7 && strcasecmp(name, "WWExist") == 0) { return 0x8F2; }
if (len == 9 && strcasecmp(name, "WarmStart") == 0) { return 0x0CFC; }
if (len == 10 && strcasecmp(name, "WindowList") == 0) { return 0x9D6; }
if (len == 10 && strcasecmp(name, "WordRedraw") == 0) { return 0xBA5; }


	}
	return -1;
}

void help(void)
{
	fprintf(stdout, "Usage: ReadGlobal [-1 | -2 | -4 | -b] [-h] global\n");
}

int getopt(char *opts, int argc, char **argv)
{
	int i = 0;

	for (i = 1; i < argc; ++i)
	{
		char *str = argv[i];
		char c = str[0];

		if (c != '-') return i;
		++str;

		// -- to terminate
		if (str[0] == '-' && str[1] == 0)
			return i + 1;

		for (; *str; ++str)
		{
			c = *str;
			switch(c)
			{
				case '1':
				case '2':
				case '4':
					opts['4' - '0'] = 0;
					opts['2' - '0'] = 0;
					opts['1' - '0'] = 0;
					opts['b' - 'a' + 10] = 0;
					opts[c - '0'] = 1;
					break;

				case 'b':
				case 'B':
					opts['4' - '0'] = 0;
					opts['2' - '0'] = 0;
					opts['1' - '0'] = 0;
					opts['b' - 'a' + 10] = 1;
					break;

				case 'h':
				case '?':
					help();
					exit(0);
					break;
				default:
					fprintf(stderr, "Duplicate - Invalid flag: \"%c\"\n", c);
					exit(1);
					break;

			}
		}
	}
	return i;
}


int main(int argc, char **argv)
{
	char opts[36];
	int optind;
	long address;
	unsigned size;
	unsigned long value;
	unsigned i;
	int numeric = 0;

	memset(opts, 0, sizeof(opts));

	optind = getopt(opts, argc, argv);

	argc -= optind;
	argv += optind;

	if (argc != 1) {
		help();
		exit(1);
	}


	address = GlobalAddress(argv[0], &numeric);
	if (address == -1 && numeric == 0) {
		fprintf(stderr, "Unknown Global: %s\n", argv[0]);
		exit(2);
	}

	size = 2;
	if (opts['b' - 'a' + 10]) size = 1;
	if (opts[1]) size = 1;
	if (opts[2]) size = 2;
	if (opts[4]) size = 4;

	value = 0;
	for (i = 0; i< size; ++i)
	{
		value = value << 8;
		value = value + ((unsigned char *)address)[i];
	}

	if (numeric) {
		if (address > 0xffff)
			printf("%ld ($%06lx):", address, address);
		else
			printf("%d ($%04x):", (unsigned)address, (unsigned)address);
	} else {
		printf("%s ($%04x):", argv[0], address);
	}

	if (size == 1) {
		printf(" $%02x", value);
		printf(" %u", value);
		if (value & 0x80) printf(" %d", (signed char)value);
		if (opts['b' - 'a' + 10]) printf(" %s", value ? "True" : "False");
	}
	if (size == 2) {
		printf(" $%04x", value);
		if (value & 0x8000) printf(" -$%04x", ~value + 1);
		printf(" %u", value);
		if (value & 0x8000) printf(" %d", (signed short)value);
	}

	if (size == 4) {
		printf(" $%08lx", value);
		if (value & 0x80000000) printf(" -$%08lx", ~value + 1);
		printf(" %u", value);
		if (value & 0x80000000) printf(" %ld", (signed long)value);
	}

	printf("\n");
	exit(0);
	return 0;
}
