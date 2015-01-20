#include <Finder.h>
#include <Files.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>

int strcasecmp(const char *s1, const char *s2)
{
  int a, b;
  for (;;)
  {
    a = tolower(*s1++);
    b = tolower(*s2++);

    if (a < b) return -1;
    if (a > b) return 1;

    // a == b.
    if (a == 0) return 0;

  }
}

#define msizeof(type, member) sizeof( ((type *)0)->member)

void dump_AccessParam(void)
{
  printf("/ *AccessParam */\n");

  printf("_qLink = %u,\n", offsetof(AccessParam, qLink));
  printf("_qType = %u,\n", offsetof(AccessParam, qType));
  printf("_ioTrap = %u,\n", offsetof(AccessParam, ioTrap));
  printf("_ioCmdAddr = %u,\n", offsetof(AccessParam, ioCmdAddr));
  printf("_ioCompletion = %u,\n", offsetof(AccessParam, ioCompletion));
  printf("_ioResult = %u,\n", offsetof(AccessParam, ioResult));
  printf("_ioNamePtr = %u,\n", offsetof(AccessParam, ioNamePtr));
  printf("_ioVRefNum = %u,\n", offsetof(AccessParam, ioVRefNum));
  printf("_filler3 = %u,\n", offsetof(AccessParam, filler3));
  printf("_ioDenyModes = %u,\n", offsetof(AccessParam, ioDenyModes));
  printf("_filler4 = %u,\n", offsetof(AccessParam, filler4));
  printf("_filler5 = %u,\n", offsetof(AccessParam, filler5));
  printf("_ioACUser = %u,\n", offsetof(AccessParam, ioACUser));
  printf("_filler6 = %u,\n", offsetof(AccessParam, filler6));
  printf("_ioACOwnerID = %u,\n", offsetof(AccessParam, ioACOwnerID));
  printf("_ioACGroupID = %u,\n", offsetof(AccessParam, ioACGroupID));
  printf("_ioACAccess = %u,\n", offsetof(AccessParam, ioACAccess));
  printf("_ioDirID = %u,\n", offsetof(AccessParam, ioDirID));

  printf("\n");
  printf("\n");

}

void dump_DirInfo(void)
{
  printf("/* DirInfo */\n");

  printf("_qLink = %u,\n", offsetof(DirInfo, qLink));
  printf("_qType = %u,\n", offsetof(DirInfo, qType));
  printf("_ioTrap = %u,\n", offsetof(DirInfo, ioTrap));
  printf("_ioCmdAddr = %u,\n", offsetof(DirInfo, ioCmdAddr));
  printf("_ioCompletion = %u,\n", offsetof(DirInfo, ioCompletion));
  printf("_ioResult = %u,\n", offsetof(DirInfo, ioResult));
  printf("_ioNamePtr = %u,\n", offsetof(DirInfo, ioNamePtr));
  printf("_ioVRefNum = %u,\n", offsetof(DirInfo, ioVRefNum));
  printf("_ioFRefNum = %u,\n", offsetof(DirInfo, ioFRefNum));
  printf("_ioFVersNum = %u,\n", offsetof(DirInfo, ioFVersNum));
  printf("_filler1 = %u,\n", offsetof(DirInfo, filler1));
  printf("_ioFDirIndex = %u,\n", offsetof(DirInfo, ioFDirIndex));
  printf("_ioFlAttrib = %u,\n", offsetof(DirInfo, ioFlAttrib));
  printf("_ioACUser = %u,\n", offsetof(DirInfo, ioACUser));
  printf("_ioDrUsrWds = %u,\n", offsetof(DirInfo, ioDrUsrWds));
  printf("_ioDrDirID = %u,\n", offsetof(DirInfo, ioDrDirID));
  printf("_ioDrNmFls = %u,\n", offsetof(DirInfo, ioDrNmFls));
  printf("_filler3 = %u,\n", offsetof(DirInfo, filler3));
  printf("_ioDrCrDat = %u,\n", offsetof(DirInfo, ioDrCrDat));
  printf("_ioDrMdDat = %u,\n", offsetof(DirInfo, ioDrMdDat));
  printf("_ioDrBkDat = %u,\n", offsetof(DirInfo, ioDrBkDat));
  printf("_ioDrFndrInfo = %u,\n", offsetof(DirInfo, ioDrFndrInfo));
  printf("_ioDrParID = %u,\n", offsetof(DirInfo, ioDrParID));

  printf("\n");
  printf("\n");
}

void dump_FileParam(void)
{
  printf("/* FileParam */\n");

  printf("_qLink = %u,\n", offsetof(FileParam, qLink));
  printf("_qType = %u,\n", offsetof(FileParam, qType));
  printf("_ioTrap = %u,\n", offsetof(FileParam, ioTrap));
  printf("_ioCmdAddr = %u,\n", offsetof(FileParam, ioCmdAddr));
  printf("_ioCompletion = %u,\n", offsetof(FileParam, ioCompletion));
  printf("_ioResult = %u,\n", offsetof(FileParam, ioResult));
  printf("_ioNamePtr = %u,\n", offsetof(FileParam, ioNamePtr));
  printf("_ioVRefNum = %u,\n", offsetof(FileParam, ioVRefNum));
  printf("_ioFRefNum = %u,\n", offsetof(FileParam, ioFRefNum));
  printf("_ioFVersNum = %u,\n", offsetof(FileParam, ioFVersNum));
  printf("_filler1 = %u,\n", offsetof(FileParam, filler1));
  printf("_ioFDirIndex = %u,\n", offsetof(FileParam, ioFDirIndex));
  printf("_ioFlAttrib = %u,\n", offsetof(FileParam, ioFlAttrib));
  printf("_ioFlVersNum = %u,\n", offsetof(FileParam, ioFlVersNum));
  printf("_ioFlFndrInfo = %u,\n", offsetof(FileParam, ioFlFndrInfo));
  printf("_ioFlNum = %u,\n", offsetof(FileParam, ioFlNum));
  printf("_ioFlStBlk = %u,\n", offsetof(FileParam, ioFlStBlk));
  printf("_ioFlLgLen = %u,\n", offsetof(FileParam, ioFlLgLen));
  printf("_ioFlPyLen = %u,\n", offsetof(FileParam, ioFlPyLen));
  printf("_ioFlRStBlk = %u,\n", offsetof(FileParam, ioFlRStBlk));
  printf("_ioFlRLgLen = %u,\n", offsetof(FileParam, ioFlRLgLen));
  printf("_ioFlRPyLen = %u,\n", offsetof(FileParam, ioFlRPyLen));
  printf("_ioFlCrDat = %u,\n", offsetof(FileParam, ioFlCrDat));
  printf("_ioFlMdDat = %u,\n", offsetof(FileParam, ioFlMdDat));

  printf("\n");
  printf("\n");
}

void dump_HFileInfo(void)
{
  printf("/* HFileInfo */\n");

  printf("_qLink = %u,\n", offsetof(HFileInfo, qLink));
  printf("_qType = %u,\n", offsetof(HFileInfo, qType));
  printf("_ioTrap = %u,\n", offsetof(HFileInfo, ioTrap));
  printf("_ioCmdAddr = %u,\n", offsetof(HFileInfo, ioCmdAddr));
  printf("_ioCompletion = %u,\n", offsetof(HFileInfo, ioCompletion));
  printf("_ioResult = %u,\n", offsetof(HFileInfo, ioResult));
  printf("_ioNamePtr = %u,\n", offsetof(HFileInfo, ioNamePtr));
  printf("_ioVRefNum = %u,\n", offsetof(HFileInfo, ioVRefNum));
  printf("_ioFRefNum = %u,\n", offsetof(HFileInfo, ioFRefNum));
  printf("_ioFVersNum = %u,\n", offsetof(HFileInfo, ioFVersNum));
  printf("_filler1 = %u,\n", offsetof(HFileInfo, filler1));
  printf("_ioFDirIndex = %u,\n", offsetof(HFileInfo, ioFDirIndex));
  printf("_ioFlAttrib = %u,\n", offsetof(HFileInfo, ioFlAttrib));
  printf("_ioACUser = %u,\n", offsetof(HFileInfo, ioACUser));
  printf("_ioFlFndrInfo = %u,\n", offsetof(HFileInfo, ioFlFndrInfo));
  printf("_ioDirID = %u,\n", offsetof(HFileInfo, ioDirID));
  printf("_ioFlStBlk = %u,\n", offsetof(HFileInfo, ioFlStBlk));
  printf("_ioFlLgLen = %u,\n", offsetof(HFileInfo, ioFlLgLen));
  printf("_ioFlPyLen = %u,\n", offsetof(HFileInfo, ioFlPyLen));
  printf("_ioFlRStBlk = %u,\n", offsetof(HFileInfo, ioFlRStBlk));
  printf("_ioFlRLgLen = %u,\n", offsetof(HFileInfo, ioFlRLgLen));
  printf("_ioFlRPyLen = %u,\n", offsetof(HFileInfo, ioFlRPyLen));
  printf("_ioFlCrDat = %u,\n", offsetof(HFileInfo, ioFlCrDat));
  printf("_ioFlMdDat = %u,\n", offsetof(HFileInfo, ioFlMdDat));
  printf("_ioFlBkDat = %u,\n", offsetof(HFileInfo, ioFlBkDat));
  printf("_ioFlXFndrInfo = %u,\n", offsetof(HFileInfo, ioFlXFndrInfo));
  printf("_ioFlParID = %u,\n", offsetof(HFileInfo, ioFlParID));
  printf("_ioFlClpSiz = %u,\n", offsetof(HFileInfo, ioFlClpSiz));

  printf("\n");
  printf("\n");
}

void dump_HFileParam()
{
  printf("/* HFileParam */\n");

  printf("_qLink = %u,\n", offsetof(HFileParam, qLink));
  printf("_qType = %u,\n", offsetof(HFileParam, qType));
  printf("_ioTrap = %u,\n", offsetof(HFileParam, ioTrap));
  printf("_ioCmdAddr = %u,\n", offsetof(HFileParam, ioCmdAddr));
  printf("_ioCompletion = %u,\n", offsetof(HFileParam, ioCompletion));
  printf("_ioResult = %u,\n", offsetof(HFileParam, ioResult));
  printf("_ioNamePtr = %u,\n", offsetof(HFileParam, ioNamePtr));
  printf("_ioVRefNum = %u,\n", offsetof(HFileParam, ioVRefNum));
  printf("_ioFRefNum = %u,\n", offsetof(HFileParam, ioFRefNum));
  printf("_ioFVersNum = %u,\n", offsetof(HFileParam, ioFVersNum));
  printf("_filler1 = %u,\n", offsetof(HFileParam, filler1));
  printf("_ioFDirIndex = %u,\n", offsetof(HFileParam, ioFDirIndex));
  printf("_ioFlAttrib = %u,\n", offsetof(HFileParam, ioFlAttrib));
  printf("_ioFlVersNum = %u,\n", offsetof(HFileParam, ioFlVersNum));
  printf("_ioFlFndrInfo = %u,\n", offsetof(HFileParam, ioFlFndrInfo));
  printf("_ioDirID = %u,\n", offsetof(HFileParam, ioDirID));
  printf("_ioFlStBlk = %u,\n", offsetof(HFileParam, ioFlStBlk));
  printf("_ioFlLgLen = %u,\n", offsetof(HFileParam, ioFlLgLen));
  printf("_ioFlPyLen = %u,\n", offsetof(HFileParam, ioFlPyLen));
  printf("_ioFlRStBlk = %u,\n", offsetof(HFileParam, ioFlRStBlk));
  printf("_ioFlRLgLen = %u,\n", offsetof(HFileParam, ioFlRLgLen));
  printf("_ioFlRPyLen = %u,\n", offsetof(HFileParam, ioFlRPyLen));
  printf("_ioFlCrDat = %u,\n", offsetof(HFileParam, ioFlCrDat));
  printf("_ioFlMdDat = %u,\n", offsetof(HFileParam, ioFlMdDat));

  printf("\n");
  printf("\n");
};



void dump_HIOParam(void)
{
  printf("/* HIOParam */\n");

  printf("_qLink = %u,\n", offsetof(HIOParam, qLink));
  printf("_qType = %u,\n", offsetof(HIOParam, qType));
  printf("_ioTrap = %u,\n", offsetof(HIOParam, ioTrap));
  printf("_ioCmdAddr = %u,\n", offsetof(HIOParam, ioCmdAddr));
  printf("_ioCompletion = %u,\n", offsetof(HIOParam, ioCompletion));
  printf("_ioResult = %u,\n", offsetof(HIOParam, ioResult));
  printf("_ioNamePtr = %u,\n", offsetof(HIOParam, ioNamePtr));
  printf("_ioVRefNum = %u,\n", offsetof(HIOParam, ioVRefNum));
  printf("_ioRefNum = %u,\n", offsetof(HIOParam, ioRefNum));
  printf("_ioVersNum = %u,\n", offsetof(HIOParam, ioVersNum));
  printf("_ioPermssn = %u,\n", offsetof(HIOParam, ioPermssn));
  printf("_ioMisc = %u,\n", offsetof(HIOParam, ioMisc));
  printf("_ioBuffer = %u,\n", offsetof(HIOParam, ioBuffer));
  printf("_ioReqCount = %u,\n", offsetof(HIOParam, ioReqCount));
  printf("_ioActCount = %u,\n", offsetof(HIOParam, ioActCount));
  printf("_ioPosMode = %u,\n", offsetof(HIOParam, ioPosMode));
  printf("_ioPosOffset = %u,\n", offsetof(HIOParam, ioPosOffset));

  printf("\n");
  printf("\n");
}

void dump_HVolumeParam(void)
{
  printf("/* HVolumeParam */\n");

  printf("_qLink = %u,\n", offsetof(HVolumeParam, qLink));
  printf("_qType = %u,\n", offsetof(HVolumeParam, qType));
  printf("_ioTrap = %u,\n", offsetof(HVolumeParam, ioTrap));
  printf("_ioCmdAddr = %u,\n", offsetof(HVolumeParam, ioCmdAddr));
  printf("_ioCompletion = %u,\n", offsetof(HVolumeParam, ioCompletion));
  printf("_ioResult = %u,\n", offsetof(HVolumeParam, ioResult));
  printf("_ioNamePtr = %u,\n", offsetof(HVolumeParam, ioNamePtr));
  printf("_ioVRefNum = %u,\n", offsetof(HVolumeParam, ioVRefNum));
  printf("_filler2 = %u,\n", offsetof(HVolumeParam, filler2));
  printf("_ioVolIndex = %u,\n", offsetof(HVolumeParam, ioVolIndex));
  printf("_ioVCrDate = %u,\n", offsetof(HVolumeParam, ioVCrDate));
  printf("_ioVLsMod = %u,\n", offsetof(HVolumeParam, ioVLsMod));
  printf("_ioVAtrb = %u,\n", offsetof(HVolumeParam, ioVAtrb));
  printf("_ioVNmFls = %u,\n", offsetof(HVolumeParam, ioVNmFls));
  printf("_ioVBitMap = %u,\n", offsetof(HVolumeParam, ioVBitMap));
  printf("_ioAllocPtr = %u,\n", offsetof(HVolumeParam, ioAllocPtr));
  printf("_ioVNmAlBlks = %u,\n", offsetof(HVolumeParam, ioVNmAlBlks));
  printf("_ioVAlBlkSiz = %u,\n", offsetof(HVolumeParam, ioVAlBlkSiz));
  printf("_ioVClpSiz = %u,\n", offsetof(HVolumeParam, ioVClpSiz));
  printf("_ioAlBlSt = %u,\n", offsetof(HVolumeParam, ioAlBlSt));
  printf("_ioVNxtCNID = %u,\n", offsetof(HVolumeParam, ioVNxtCNID));
  printf("_ioVFrBlk = %u,\n", offsetof(HVolumeParam, ioVFrBlk));
  printf("_ioVSigWord = %u,\n", offsetof(HVolumeParam, ioVSigWord));
  printf("_ioVDrvInfo = %u,\n", offsetof(HVolumeParam, ioVDrvInfo));
  printf("_ioVDRefNum = %u,\n", offsetof(HVolumeParam, ioVDRefNum));
  printf("_ioVFSID = %u,\n", offsetof(HVolumeParam, ioVFSID));
  printf("_ioVBkUp = %u,\n", offsetof(HVolumeParam, ioVBkUp));
  printf("_ioVSeqNum = %u,\n", offsetof(HVolumeParam, ioVSeqNum));
  printf("_ioVWrCnt = %u,\n", offsetof(HVolumeParam, ioVWrCnt));
  printf("_ioVFilCnt = %u,\n", offsetof(HVolumeParam, ioVFilCnt));
  printf("_ioVDirCnt = %u,\n", offsetof(HVolumeParam, ioVDirCnt));
  printf("_ioVFndrInfo = %u,\n", offsetof(HVolumeParam, ioVFndrInfo));

  printf("\n");
  printf("\n");
}

void dump_IOParam(void)
{
  printf("/* IOParam */\n");

  printf("_qLink = %u,\n", offsetof(IOParam, qLink));
  printf("_qType = %u,\n", offsetof(IOParam, qType));
  printf("_ioTrap = %u,\n", offsetof(IOParam, ioTrap));
  printf("_ioCmdAddr = %u,\n", offsetof(IOParam, ioCmdAddr));
  printf("_ioCompletion = %u,\n", offsetof(IOParam, ioCompletion));
  printf("_ioResult = %u,\n", offsetof(IOParam, ioResult));
  printf("_ioNamePtr = %u,\n", offsetof(IOParam, ioNamePtr));
  printf("_ioVRefNum = %u,\n", offsetof(IOParam, ioVRefNum));
  printf("_ioRefNum = %u,\n", offsetof(IOParam, ioRefNum));
  printf("_ioVersNum = %u,\n", offsetof(IOParam, ioVersNum));
  printf("_ioPermssn = %u,\n", offsetof(IOParam, ioPermssn));
  printf("_ioMisc = %u,\n", offsetof(IOParam, ioMisc));
  printf("_ioBuffer = %u,\n", offsetof(IOParam, ioBuffer));
  printf("_ioReqCount = %u,\n", offsetof(IOParam, ioReqCount));
  printf("_ioActCount = %u,\n", offsetof(IOParam, ioActCount));
  printf("_ioPosMode = %u,\n", offsetof(IOParam, ioPosMode));
  printf("_ioPosOffset = %u,\n", offsetof(IOParam, ioPosOffset));

  printf("\n");
  printf("\n");
}

void dump_VolumeParam(void)
{
  printf("/* VolumeParam */\n");

  printf("_qLink = %u,\n", offsetof(VolumeParam, qLink));
  printf("_qType = %u,\n", offsetof(VolumeParam, qType));
  printf("_ioTrap = %u,\n", offsetof(VolumeParam, ioTrap));
  printf("_ioCmdAddr = %u,\n", offsetof(VolumeParam, ioCmdAddr));
  printf("_ioCompletion = %u,\n", offsetof(VolumeParam, ioCompletion));
  printf("_ioResult = %u,\n", offsetof(VolumeParam, ioResult));
  printf("_ioNamePtr = %u,\n", offsetof(VolumeParam, ioNamePtr));
  printf("_ioVRefNum = %u,\n", offsetof(VolumeParam, ioVRefNum));
  printf("_filler2 = %u,\n", offsetof(VolumeParam, filler2));
  printf("_ioVolIndex = %u,\n", offsetof(VolumeParam, ioVolIndex));
  printf("_ioVCrDate = %u,\n", offsetof(VolumeParam, ioVCrDate));
  printf("_ioVLsBkUp = %u,\n", offsetof(VolumeParam, ioVLsBkUp));
  printf("_ioVAtrb = %u,\n", offsetof(VolumeParam, ioVAtrb));
  printf("_ioVNmFls = %u,\n", offsetof(VolumeParam, ioVNmFls));
  printf("_ioVDirSt = %u,\n", offsetof(VolumeParam, ioVDirSt));
  printf("_ioVBlLn = %u,\n", offsetof(VolumeParam, ioVBlLn));
  printf("_ioVNmAlBlks = %u,\n", offsetof(VolumeParam, ioVNmAlBlks));
  printf("_ioVAlBlkSiz = %u,\n", offsetof(VolumeParam, ioVAlBlkSiz));
  printf("_ioVClpSiz = %u,\n", offsetof(VolumeParam, ioVClpSiz));
  printf("_ioAlBlSt = %u,\n", offsetof(VolumeParam, ioAlBlSt));
  printf("_ioVNxtFNum = %u,\n", offsetof(VolumeParam, ioVNxtFNum));
  printf("_ioVFrBlk = %u,\n", offsetof(VolumeParam, ioVFrBlk));

  printf("\n");
  printf("\n");
}

void dump_WDPBRec(void)
{
  printf("/* WDPBRec */\n");

  printf("_qLink = %u,\n", offsetof(WDPBRec, qLink));
  printf("_qType = %u,\n", offsetof(WDPBRec, qType));
  printf("_ioTrap = %u,\n", offsetof(WDPBRec, ioTrap));
  printf("_ioCmdAddr = %u,\n", offsetof(WDPBRec, ioCmdAddr));
  printf("_ioCompletion = %u,\n", offsetof(WDPBRec, ioCompletion));
  printf("_ioResult = %u,\n", offsetof(WDPBRec, ioResult));
  printf("_ioNamePtr = %u,\n", offsetof(WDPBRec, ioNamePtr));
  printf("_ioVRefNum = %u,\n", offsetof(WDPBRec, ioVRefNum));
  printf("_filler1 = %u,\n", offsetof(WDPBRec, filler1));
  printf("_ioWDIndex = %u,\n", offsetof(WDPBRec, ioWDIndex));
  printf("_ioWDProcID = %u,\n", offsetof(WDPBRec, ioWDProcID));
  printf("_ioWDVRefNum = %u,\n", offsetof(WDPBRec, ioWDVRefNum));
  printf("_filler2 = %u,\n", offsetof(WDPBRec, filler2));
  printf("_ioWDDirID = %u,\n", offsetof(WDPBRec, ioWDDirID));

  printf("\n");
  printf("\n");
}

void dump_SysEnvRec(void)
{
  printf("/* SysEnvRec */\n");

  printf("_environsVersion = %u,\n", offsetof(SysEnvRec, environsVersion));
  printf("_machineType = %u,\n", offsetof(SysEnvRec, machineType));
  printf("_systemVersion = %u,\n", offsetof(SysEnvRec, systemVersion));
  printf("_processor = %u,\n", offsetof(SysEnvRec, processor));
  printf("_hasFPU = %u,\n", offsetof(SysEnvRec, hasFPU));
  printf("_hasColorQD = %u,\n", offsetof(SysEnvRec, hasColorQD));
  printf("_keyBoardType = %u,\n", offsetof(SysEnvRec, keyBoardType));
  printf("_atDrvrVersNum = %u,\n", offsetof(SysEnvRec, atDrvrVersNum));
  printf("_sysVRefNum = %u,\n", offsetof(SysEnvRec, sysVRefNum));

  printf("\n");
  printf("\n");
}



#define DUMP(xname) if (strcasecmp(name, #xname) == 0) { dump_ ## xname(); continue; }
int main(int argc, char **argv)
{
  int i;

  if (argc == 1)
  {
    dump_AccessParam();
    dump_DirInfo();
    dump_HFileInfo();
    dump_HFileParam();
    dump_HIOParam();
    dump_HVolumeParam();
    dump_FileParam();
    dump_IOParam();
    dump_VolumeParam();
    dump_WDPBRec();
    dump_SysEnvRec();
  }

  for (i = 1; i < argc; ++i)
  {
    const char *name = argv[i];
    switch (tolower(name[0]))
    {
      case 'a':
        DUMP(AccessParam)
        break;

      case 'd':
        DUMP(DirInfo)
        break;

      case 'f':
        DUMP(FileParam);
        break;

      case 'h':
        DUMP(HFileInfo)
        DUMP(HFileParam)
        DUMP(HIOParam)
        DUMP(HVolumeParam)
        break;

      case 'i':
        DUMP(IOParam);
        break;

      case 's':
        DUMP(SysEnvRec);
        break;

      case 'v':
        DUMP(VolumeParam);
        break;

      case 'w':
        DUMP(WDPBRec)
        break;
    }

    fprintf(stderr, "Unsupported struct: %s\n", name);
  }

  return 0;
}