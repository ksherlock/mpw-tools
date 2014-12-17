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

int main(int argc, char **argv)
{
  int i;

  if (argc == 1)
  {
    dump_DirInfo();
    dump_HFileInfo();
    dump_WDPBRec();
  }

  for (i = 1; i < argc; ++i)
  {
    const char *name = argv[i];
    if (strcasecmp(name, "DirInfo") == 0) { dump_DirInfo(); continue; }
    if (strcasecmp(name, "HFileInfo") == 0) { dump_HFileInfo(); continue; }
    if (strcasecmp(name, "WDPBRec") == 0) { dump_WDPBRec(); continue; }
    fprintf(stderr, "Unsupported struct: %s\n", name);
  }

  return 0;
}